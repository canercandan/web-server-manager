/* call.c --- 
 * 
 * Filename: call.c
 * Description: 
 * Author: Caner Candan
 * Maintainer: 
 * Created: Mon Jan  5 22:49:26 2009 (+0200)
 * Version: 
 * Last-Updated: Sun Mar  1 13:12:38 2009 (+0200)
 *           By: Caner Candan
 *     Update #: 215
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

#include <escienta.h>

char	user[] = "demo";
char	passwd[] = "demo";

static int	on_load(void)
{
  return (0);
}

static void	on_unload(void)
{
}

static t_res	login(t_hook_result *t)
{
  t_client	*client;
  t_client_data	*cd;

  client = t->data;
  cd = client->data;
  if (select_mesg_cmp_field(client, user, 1) == 0 &&
      select_mesg_cmp_field(client, passwd, 2) == 0)
    {
      cd->stat = STAT_IN;
      //select_send(client, "login tuit tuit\n");
      return (R_END);
    }
  return (R_ERROR);
}

static t_res	logout(t_hook_result *t)
{
  t_client	*client;
  t_client_data	*cd;

  client = t->data;
  cd = client->data;
  cd->stat = STAT_OUT;
  return (R_END);
}

static t_res	status(t_hook_result *t)
{
  t_client	*client;
  t_client_data	*cd;

  client = t->data;
  cd = client->data;
  return ((cd->stat == STAT_IN) ? R_END : R_ERROR);
}

void	call(t_module *t)
{
  loadmod_set_module_name(t, "auth", 0.1);
  loadmod_set_module_callback(t, on_load, on_unload);
  loadmod_add_hook_point(t, "login", MIDDLE, login);
  loadmod_add_hook_point(t, "logout", MIDDLE, logout);
  loadmod_add_hook_point(t, "status", MIDDLE, status);
}

/* call.c ends here */
