/* addclient_callback.c --- 
 * 
 * Filename: addclient_callback.c
 * Description: 
 * Author: Caner Candan
 * Maintainer: 
 * Created: Sat Feb  7 00:49:01 2009 (+0200)
 * Version: 
 * Last-Updated: Sat Feb  7 01:07:04 2009 (+0200)
 *           By: Caner Candan
 *     Update #: 11
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

#include <stdlib.h>
#include "webserver.h"

void	addclient_callback(t_select *select, t_client *client)
{
  t_client_data	*cd;

  (void)select;
  cd = malloc(sizeof(*cd));
  cd->stat = STAT_OUT;
  client->data = (void*)cd;
}

/* addclient_callback.c ends here */
