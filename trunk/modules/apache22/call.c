/* call.c --- 
 * 
 * Filename: call.c
 * Description: 
 * Author: Caner Candan
 * Maintainer: 
 * Created: Mon Jan  5 22:49:26 2009 (+0200)
 * Version: 
 * Last-Updated: Tue Mar  3 11:17:44 2009 (+0200)
 *           By: Caner Candan
 *     Update #: 392
 * URL: 
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */

/* This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301, USA.
 */

/* Code: */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <escienta.h>
#include "apache22.h"

static void	reload_apache()
{
  pid_t		pid;

  if ((pid = fork()) == 0)
    {
      execl("/usr/local/etc/rc.d/apache22",
	    "apache22", "reload", (char*)0);
      exit(-1);
    }
}

static int	get_id()
{
  char		buf[BUFF_SIZE];
  char		path[BUFF_SIZE];
  int		nb;
  int		fd;

  snprintf(path, BUFF_SIZE, "%s/%s", CONF_DIR, ID_FILE);
  if ((fd = open(path, O_RDONLY | O_CREAT, 0644)) < 0)
    return (0);
  if ((nb = read(fd, buf, BUFF_SIZE)) < 0)
    return (0);
  close(fd);
  buf[nb] = 0;
#ifdef DEBUG
  printf("*** readding [%s] [%d]\n", buf, nb);
#endif /* !DEBUG */
  if (nb == 0)
    return (0);
  return (atoi(buf));
}

static void	set_next_id()
{
  char		buf[BUFF_SIZE];
  char		path[BUFF_SIZE];
  int		fd;
  int		nextid;

  nextid = get_id() + 1;
#ifdef DEBUG
  printf("*** writting [%d]\n", nextid);
#endif /* !DEBUG */
  snprintf(buf, BUFF_SIZE, "%d", nextid);
  snprintf(path, BUFF_SIZE, "%s/%s", CONF_DIR, ID_FILE);
  if ((fd = open(path, O_WRONLY | O_CREAT, 0644)) < 0)
    return;
  write(fd, buf, strlen(buf));
  close(fd);
}

static int	on_load(void)
{
  return (0);
}

static void	on_unload(void)
{
  reload_apache();
}

static t_res	create(t_hook_result *t)
{
  char		buf[BUFF_SIZE];
  char		path[BUFF_SIZE];
  int		id;
  int		fd;
  char		buf2[1024];
  char		*domain;
  t_client	*client;

  client = t->data;
  if ((domain = select_recv_field(client, 1)) == NULL)
    return (R_ERROR);
  set_next_id();
  id = get_id();

  snprintf(path, BUFF_SIZE, "%s/%d", HOST_DIR, id);
  mkdir(path, 0777);
  snprintf(path, BUFF_SIZE, "%s/%d/www", HOST_DIR, id);
  mkdir(path, 0777);
  snprintf(path, BUFF_SIZE, "%s/%d/logs", HOST_DIR, id);
  mkdir(path, 0777);

  snprintf(path, BUFF_SIZE, "%s/%d", CONF_DIR, id);
  mkdir(path, 0777);

  snprintf(path, BUFF_SIZE, "%s/%d/main.conf", CONF_DIR, id);
  if ((fd = open(path, O_WRONLY | O_CREAT, 0644)) < 0)
    return (R_ERROR);
  snprintf(buf2, 1024, VIRTUALHOST,
	   HOST_DIR, id,
	   domain, domain,
	   HOST_DIR, id,
	   HOST_DIR, id,
	   HOST_DIR, id);
  write(fd, buf2, strlen(buf2));
  close(fd);

  snprintf(path, BUFF_SIZE, "%s/%d/%s", HOST_DIR, id, DOMAIN_FILE);
  if ((fd = open(path, O_WRONLY | O_CREAT, 0644)) < 0)
    return (R_ERROR);
  write(fd, domain, strlen(domain));
  close(fd);
  free(domain);

  snprintf(buf, BUFF_SIZE, "web_create %d\n", id);
  select_send((t_client*)t->data, buf);
  return (R_END);
}

static t_res	delete(t_hook_result *t)
{
  t_client	*client;
  char		*tmp;
  int		id;
  char		path[BUFF_SIZE];

  client = t->data;
  if ((tmp = select_recv_field(client, 1)) == NULL)
    return (R_ERROR);
  id = atoi(tmp);
  free(tmp);

  snprintf(path, BUFF_SIZE, "%s/%d/main.conf", CONF_DIR, id);
  unlink(path);
  snprintf(path, BUFF_SIZE, "%s/%d", CONF_DIR, id);
  rmdir(path);

  snprintf(path, BUFF_SIZE, "%s/%d/%s", HOST_DIR, id, DOMAIN_FILE);
  unlink(path);

  snprintf(path, BUFF_SIZE, "%s/%d/logs", HOST_DIR, id);
  rmdir(path);
  snprintf(path, BUFF_SIZE, "%s/%d/www", HOST_DIR, id);
  rmdir(path);
  snprintf(path, BUFF_SIZE, "%s/%d", HOST_DIR, id);
  rmdir(path);

  return (R_END);
}

void	call(t_module *t)
{
  loadmod_set_module_name(t, "apache22", 0.1);
  loadmod_set_module_callback(t, on_load, on_unload);
  loadmod_add_hook_point(t, "web_create", MIDDLE, create);
  loadmod_add_hook_point(t, "web_delete", MIDDLE, delete);
}

/* call.c ends here */
