// escienta.h --- 
// 
// Filename: escienta.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Mon Feb  2 17:15:52 2009 (+0200)
// Version: 
// Last-Updated: Sat Feb  7 01:01:21 2009 (+0200)
//           By: Caner Candan
//     Update #: 14
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

#ifndef __ESCIENTA_H__
# define __ESCIENTA_H__

# include <loadmod.h>
# include <select.h>

/*
** defines
*/

/*
** type definitions
*/

/*
** enumerators
*/

typedef enum {STAT_IN, STAT_OUT}	t_client_stat;

/*
** structures
*/

typedef struct	s_client_data
{
  t_client_stat	stat;
}		t_client_data;

/*
** variables
*/

/*
** functions
*/

void	recv_callback(t_select*, t_client*);
void	addclient_callback(t_select*, t_client*);
void	delclient_callback(t_select*, t_client*);

#endif /* !__ESCIENTA_H__ */

// 
// escienta.h ends here
