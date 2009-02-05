/* recv_callback.c --- 
 * 
 * Filename: recv_callback.c
 * Description: 
 * Author: Caner Candan
 * Maintainer: 
 * Created: Mon Feb  2 17:18:26 2009 (+0200)
 * Version: 
 * Last-Updated: Thu Feb  5 14:45:53 2009 (+0200)
 *           By: Caner Candan
 *     Update #: 24
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

  (void)select;
  if (select_mesg_cmp(client, "") == 0)
    return;
  t = loadmod_init("modules/enabled");
  loadmod_exec_hook_point(t, "init", (void*)client);
  loadmod_exec_hook_point(t, "recv", (void*)client);

  if (select_mesg_cmp_field(client, "create_web_site", 0) == 0)
    {
      select_send(client, "create_web_site ok\n");
      loadmod_exec_hook_point(t, "create_web_site", (void*)client);
    }
  else if (select_mesg_cmp_field(client, "delete_web_site", 0) == 0)
    {
      select_send(client, "delete_web_site ok\n");
      loadmod_exec_hook_point(t, "delete_web_site", (void*)client);
    }

  loadmod_exec_hook_point(t, "end", (void*)client);
  loadmod_free(t);
}

/* recv_callback.c ends here */
