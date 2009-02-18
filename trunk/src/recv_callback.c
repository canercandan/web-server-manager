/* recv_callback.c --- 
 * 
 * Filename: recv_callback.c
 * Description: 
 * Author: Caner Candan
 * Maintainer: 
 * Created: Mon Feb  2 17:18:26 2009 (+0200)
 * Version: 
 * Last-Updated: Thu Feb 19 01:39:44 2009 (+0200)
 *           By: Caner Candan
 *     Update #: 138
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

t_cmd	cmds[] =
  {
    {"login", STAT_OUT},
    {"logout", STAT_IN},
    {"status", STAT_NOT},
    {"web_create", STAT_IN},
    {"web_delete", STAT_IN},
    {NULL, 0}
  };

static void	cmd_exec(t_loadmod *t, t_client *client)
{
  t_client_data	*cd;
  int		i;
  char		buf[128];

  cd = client->data;
  for (i = 0; cmds[i].name != NULL; i++)
    {
      if (select_mesg_cmp_field(client, cmds[i].name, 0) == 0)
	{
	  if ((cmds[i].stat == cd->stat ||
	       cmds[i].stat == STAT_NOT) &&
	      loadmod_exec_hook_point(t, cmds[i].name, (void*)client)
	      != R_ERROR)
	    {
	      if (client->buf_write != NULL)
		snprintf(buf, 128, "%s ok\n", cmds[i].name);
	    }
	  else
	    snprintf(buf, 128, "%s ko\n", cmds[i].name);
	  select_send(client, buf);
	  return;
	}
    }
  select_send(client, "not found\n");
}

void		recv_callback(t_select *select, t_client *client)
{
  t_loadmod	*t;

  (void)select;
  if (select_mesg_cmp(client, "") == 0)
    return;
  t = loadmod_init("modules/enabled");
  loadmod_exec_hook_point(t, "init", (void*)client);
  loadmod_exec_hook_point(t, "recv", (void*)client);

  cmd_exec(t, client);

  loadmod_exec_hook_point(t, "send", (void*)client);
  loadmod_exec_hook_point(t, "end", (void*)client);
  loadmod_free(t);
}

/* recv_callback.c ends here */
