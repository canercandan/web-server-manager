// apache22.h --- 
// 
// Filename: apache22.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Mon Feb  9 10:55:58 2009 (+0200)
// Version: 
// Last-Updated: Tue Mar  3 15:01:26 2009 (+0200)
//           By: Caner Candan
//     Update #: 67
// URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change log:
// 
// 
// 
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 3, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; see the file COPYING.  If not, write to
// the Free Software Foundation, Inc., 51 Franklin Street, Fifth
// Floor, Boston, MA 02110-1301, USA.
// 
// 

// Code:

#ifndef __APACHE22_H__
# define __APACHE22_H__

/*
** defines
*/

# define CONF_DIR	"/usr/local/etc/apache22/webserver"
# define HOST_DIR	"/hosts"

# define ID_FILE	".id"
# define DOMAIN_FILE	".domain"

# define BUFF_SIZE	128

# define VIRTUALHOST				\
  "<VirtualHost *:80>\n"			\
  "ServerAdmin root@%s\n"			\
  "DocumentRoot %s/%s/www\n"			\
  "ServerName %s\n"				\
  "ServerAlias www.%s\n"			\
  "ErrorLog %s/%s/logs/error.log\n"		\
  "CustomLog %s/%s/logs/access.log common\n"	\
  "<Directory \"%s/%s/www\">\n"			\
  "AllowOverride All\n"				\
  "Order allow,deny\n"				\
  "Allow from all\n"				\
  "</Directory>\n"				\
  "</VirtualHost>\n"

/*
** type definitions
*/

/*
** enumerators
*/

/*
** structures
*/

/*
** variables
*/

/*
** functions
*/

#endif /* !__APACHE22_H__ */

// 
// apache22.h ends here
