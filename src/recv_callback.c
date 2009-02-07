/* recv_callback.c --- 
 * 
 * Filename: recv_callback.c
 * Description: 
 * Author: Caner Candan
 * Maintainer: 
 * Created: Mon Feb  2 17:18:26 2009 (+0200)
 * Version: 
 * Last-Updated: Sat Feb  7 11:01:31 2009 (+0200)
 *           By: Caner Candan
 *     Update #: 58
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

#include <stdio.h>
#include "escienta.h"

void		recv_callback(t_select *select, t_client *client)
{
  t_loadmod	*t;
  t_client_data	*cd;

  (void)select;
  if (select_mesg_cmp(client, "") == 0)
    return;
  t = loadmod_init("modules/enabled");
  loadmod_exec_hook_point(t, "init", (void*)client);
  loadmod_exec_hook_point(t, "recv", (void*)client);

  cd = client->data;

  if (select_mesg_cmp_field(client, "login", 0) == 0)
    {
      if (loadmod_exec_hook_point(t, "login", (void*)client) == R_FOUND)
	select_send(client, "login ok\n");
      else
	select_send(client, "login ko\n");
    }
  else if (select_mesg_cmp_field(client, "logout", 0) == 0)
    {
      loadmod_exec_hook_point(t, "logout", (void*)client);
    }
  else if (cd->stat == STAT_IN &&
	   select_mesg_cmp_field(client, "web_create", 0) == 0)
    {
      if (loadmod_exec_hook_point(t, "web_create", (void*)client) != R_ERROR)
	select_send(client, "web_create ok\n");
      else
	select_send(client, "web_create ko\n");
    }
  else if (cd->stat == STAT_IN &&
	   select_mesg_cmp_field(client, "web_delete", 0) == 0)
    {
      if (loadmod_exec_hook_point(t, "web_delete", (void*)client) != R_ERROR)
	select_send(client, "web_delete ok\n");
      else
	select_send(client, "web_delete ko\n");
    }
  else
    {
      select_send(client, "not found\n");
    }

  loadmod_exec_hook_point(t, "send", (void*)client);
  loadmod_exec_hook_point(t, "end", (void*)client);
  loadmod_free(t);
}

/* recv_callback.c ends here */
