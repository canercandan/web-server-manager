/* call.c --- 
 * 
 * Filename: call.c
 * Description: 
 * Author: Caner Candan
 * Maintainer: 
 * Created: Mon Jan  5 22:49:26 2009 (+0200)
 * Version: 
 * Last-Updated: Wed Mar  4 11:25:19 2009 (+0200)
 *           By: Caner Candan
 *     Update #: 433
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
#include <string.h>
#include <webserver.h>
#include "proftpd.h"

static void	reload()
{
  pid_t		pid;

  if ((pid = fork()) == 0)
    {
      execl("/usr/local/etc/rc.d/proftpd",
	    "proftpd", "reload", (char*)0);
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

  free(id);
  free(domain);

  return (R_END);
}

static t_res	delete(t_hook_result *t)
{
  t_client	*client;
  char		*id;

  client = t->data;
  if ((id = select_recv_field(client, 1)) == NULL)
    return (R_ERROR);

  free(id);

  return (R_END);
}

void	call(t_module *t)
{
  loadmod_set_module_name(t, "proftpd", 0.1);
  loadmod_set_module_callback(t, on_load, on_unload);
  loadmod_add_hook_point(t, "web_create", MIDDLE, create);
  loadmod_add_hook_point(t, "web_delete", MIDDLE, delete);
  loadmod_add_comp_version(t, 0.1, NULL);
  loadmod_add_comp_version(t, 0.2, NULL);
  loadmod_add_comp_version(t, 0.3, NULL);
}

/* call.c ends here */
