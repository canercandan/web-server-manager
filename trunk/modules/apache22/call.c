/* call.c --- 
 * 
 * Filename: call.c
 * Description: 
 * Author: Caner Candan
 * Maintainer: 
 * Created: Mon Jan  5 22:49:26 2009 (+0200)
 * Version: 
 * Last-Updated: Tue Feb 10 12:36:53 2009 (+0200)
 *           By: Caner Candan
 *     Update #: 279
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

static int	fd = 0;
static int	id = 0;

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

static int	get_next_id()
{
  char		buf[BUFF_SIZE];
  int		nb;

  if ((nb = read(fd, buf, BUFF_SIZE)) < 0)
    return (-1);
  buf[nb] = 0;
  printf("*** readding [%s] [%d]\n", buf, nb);
  if (nb == 0)
    return (1);
  return (atoi(buf));
}

static void	set_next_id()
{
  char		buf[BUFF_SIZE];

  printf("*** writting [%d]\n", get_next_id());
  snprintf(buf, BUFF_SIZE, "%d", get_next_id());
  write(fd, buf, strlen(buf));
}

static int	on_load(void)
{
  if ((fd = open(ID_FILE, O_RDWR | O_CREAT, 0644)) < 0)
    return (-1);
  printf("id [%d]\n", get_next_id());
  set_next_id();
  return (0);
}

static void	on_unload(void)
{
  reload_apache();
  close(fd);
}

static t_res	create(t_hook_result *t)
{
  (void)t;
  return (R_END);
}

static t_res	delete(t_hook_result *t)
{
  (void)t;
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
