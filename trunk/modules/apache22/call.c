/* call.c --- 
 * 
 * Filename: call.c
 * Description: 
 * Author: Caner Candan
 * Maintainer: 
 * Created: Mon Jan  5 22:49:26 2009 (+0200)
 * Version: 
 * Last-Updated: Wed Mar  4 11:21:08 2009 (+0200)
 *           By: Caner Candan
 *     Update #: 422
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

static void	reload()
{
  pid_t		pid;

  if ((pid = fork()) == 0)
    {
      execl("/usr/local/etc/rc.d/apache22",
	    "apache22", "reload", (char*)0);
      exit(-1);
    }
}

static int	on_load(void)
{
  return (0);
}

static void	on_unload(void)
{
  reload();
}

static t_res	create(t_hook_result *t)
{
  char		path[BUFF_SIZE];
  char		buf[1024];
  int		fd;
  char		*id;
  char		*domain;
  t_client	*client;

  client = t->data;
  if ((id = select_recv_field(client, 1)) == NULL)
    return (R_ERROR);
  if ((domain = select_recv_field(client, 2)) == NULL)
    {
      free(id);
      return (R_ERROR);
    }

  snprintf(path, BUFF_SIZE, "%s/%s", HOST_DIR, id);
  mkdir(path, 0777);
  snprintf(path, BUFF_SIZE, "%s/%s/www", HOST_DIR, id);
  mkdir(path, 0777);
  snprintf(path, BUFF_SIZE, "%s/%s/logs", HOST_DIR, id);
  mkdir(path, 0777);

  snprintf(path, BUFF_SIZE, "%s/%s", CONF_DIR, id);
  mkdir(path, 0777);

  snprintf(path, BUFF_SIZE, "%s/%s/main.conf", CONF_DIR, id);
  if ((fd = open(path, O_WRONLY | O_CREAT, 0644)) < 0)
    return (R_ERROR);
  snprintf(buf, 1024, VIRTUALHOST,
	   domain, HOST_DIR, id, domain, domain,
	   HOST_DIR, id, HOST_DIR, id, HOST_DIR, id);
  write(fd, buf, strlen(buf));
  close(fd);

  snprintf(path, BUFF_SIZE, "%s/%s/%s", HOST_DIR, id, ID_FILE);
  if ((fd = open(path, O_WRONLY | O_CREAT, 0644)) < 0)
    return (R_ERROR);
  write(fd, id, strlen(id));
  close(fd);

  snprintf(path, BUFF_SIZE, "%s/%s/%s", HOST_DIR, id, DOMAIN_FILE);
  if ((fd = open(path, O_WRONLY | O_CREAT, 0644)) < 0)
    return (R_ERROR);
  write(fd, domain, strlen(domain));
  close(fd);

  free(id);
  free(domain);

  return (R_END);
}

static t_res	delete(t_hook_result *t)
{
  t_client	*client;
  char		*id;
  char		path[BUFF_SIZE];

  client = t->data;
  if ((id = select_recv_field(client, 1)) == NULL)
    return (R_ERROR);

  snprintf(path, BUFF_SIZE, "%s/%s/main.conf", CONF_DIR, id);
  unlink(path);
  snprintf(path, BUFF_SIZE, "%s/%s", CONF_DIR, id);
  rmdir(path);

  snprintf(path, BUFF_SIZE, "%s/%s/%s", HOST_DIR, id, ID_FILE);
  unlink(path);

  snprintf(path, BUFF_SIZE, "%s/%s/%s", HOST_DIR, id, DOMAIN_FILE);
  unlink(path);

  snprintf(path, BUFF_SIZE, "%s/%s/logs", HOST_DIR, id);
  rmdir(path);
  snprintf(path, BUFF_SIZE, "%s/%s/www", HOST_DIR, id);
  rmdir(path);
  snprintf(path, BUFF_SIZE, "%s/%s", HOST_DIR, id);
  rmdir(path);

  free(id);
  return (R_END);
}

void	call(t_module *t)
{
  loadmod_set_module_name(t, "apache22", 0.1);
  loadmod_set_module_callback(t, on_load, on_unload);
  loadmod_add_hook_point(t, "web_create", MIDDLE, create);
  loadmod_add_hook_point(t, "web_delete", MIDDLE, delete);
  loadmod_add_comp_version(t, 0.1, NULL);
  loadmod_add_comp_version(t, 0.2, NULL);
  loadmod_add_comp_version(t, 0.3, NULL);
}

/* call.c ends here */
