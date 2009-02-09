/* call.c --- 
 * 
 * Filename: call.c
 * Description: 
 * Author: Caner Candan
 * Maintainer: 
 * Created: Mon Jan  5 22:49:26 2009 (+0200)
 * Version: 
 * Last-Updated: Mon Feb  9 18:00:21 2009 (+0200)
 *           By: Caner Candan
 *     Update #: 256
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
#include <stdio.h>
#include <escienta.h>
#include "apache22.h"

static int	fd = 0;

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

static int	next_id()
{
  char		buf[READ_SIZE];
  int		nb;

  if ((nb = read(fd, buf, READ_SIZE)) < 0)
    return (-1);
  buf[nb] = 0;
  
}

static int	on_load(void)
{
  if ((fd = open(ID_FILE, O_RDWR | O_CREAT, 0644)) < 0)
    return (-1);
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
