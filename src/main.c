/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: Caner Candan
 * Maintainer: 
 * Created: Mon Feb  2 17:15:33 2009 (+0200)
 * Version: 
 * Last-Updated: Sat Feb  7 00:46:21 2009 (+0200)
 *           By: Caner Candan
 *     Update #: 17
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

#include "escienta.h"

int		main(void)
{
  t_select	*t;

  t = select_init();
  select_set_callback(t, CB_RECV, recv_callback, NULL);
  select_set_callback(t, CB_ADDCLIENT, addclient_callback, NULL);
  select_set_callback(t, CB_DELCLIENT, delclient_callback, NULL);
  select_set_signal(t);
  select_exec(t, 4242);
  return (0);
}

/* main.c ends here */
