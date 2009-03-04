/* call.c --- 
 * 
 * Filename: call.c
 * Description: 
 * Author: Caner Candan
 * Maintainer: 
 * Created: Mon Jan  5 22:49:26 2009 (+0200)
 * Version: 
 * Last-Updated: Wed Mar  4 11:23:33 2009 (+0200)
 *           By: Caner Candan
 *     Update #: 180
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
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <escienta.h>
#include "logger.h"

static int	fd = 0;

static int	on_load(void)
{
  if ((fd = open(LOG_FILE, O_WRONLY | O_APPEND | O_CREAT, 0644)) < 0)
    return (-1);
  return (0);
}

static void	on_unload(void)
{
  close(fd);
}

static void	write_file(char *mesg)
{
  write(fd, mesg, strlen(mesg));
  printf(mesg);
}

static void	prefix(void)
{
  time_t	tm;
  char		*date;
  char		buf[128];

  time(&tm);
  date = ctime(&tm);
  date[strlen(date) - 1] = 0;
  buf[0] = 0;
  snprintf(buf, 128, "[%s] ", date);
  write_file(buf);
}

static t_res	log_init(t_hook_result *t)
{
  char		buf[128];

  (void)t;
  prefix();
  buf[0] = 0;
  snprintf(buf, 128, "init ...\n");
  write_file(buf);
  return (R_CONTINUE);
}

static t_res	log_end(t_hook_result *t)
{
  char		buf[128];

  (void)t;
  prefix();
  buf[0] = 0;
  snprintf(buf, 128, "end ...\n");
  write_file(buf);
  return (R_CONTINUE);
}

static t_res	log_recv(t_hook_result *t)
{
  char		buf[128];
  t_client	*client;

  client = t->data;
  if (select_mesg_cmp(client, "") == 0)
    return (R_END);
  prefix();
  snprintf(buf, 128, "recv ... [%s]\n", select_recv(client));
  write_file(buf);
  return (R_CONTINUE);
}

static t_res	log_send(t_hook_result *t)
{
  char		buf[128];
  t_client	*client;

  client = t->data;
  if (select_mesg_cmp(client, "") == 0)
    return (R_END);
  prefix();
  snprintf(buf, 128, "send ... [%s]\n", client->buf_write);
  write_file(buf);
  return (R_CONTINUE);
}

static t_res	log_create(t_hook_result *t)
{
  char		buf[128];
  t_client	*client;

  client = t->data;
  if (select_mesg_cmp(client, "") == 0)
    return (R_END);
  prefix();
  snprintf(buf, 128, "create web site ... [%s]\n", select_recv(client));
  write_file(buf);
  return (R_CONTINUE);
}

static t_res	log_delete(t_hook_result *t)
{
  char		buf[128];
  t_client	*client;

  client = t->data;
  if (select_mesg_cmp(client, "") == 0)
    return (R_END);
  prefix();
  snprintf(buf, 128, "delete web site ... [%s]\n", select_recv(client));
  write_file(buf);
  return (R_CONTINUE);
}

void	call(t_module *t)
{
  loadmod_set_module_name(t, "logger", 0.1);
  loadmod_set_module_callback(t, on_load, on_unload);
  loadmod_add_hook_point(t, "init", VERY_FIRST, log_init);
  loadmod_add_hook_point(t, "end", VERY_FIRST, log_end);
  loadmod_add_hook_point(t, "recv", VERY_FIRST, log_recv);
  loadmod_add_hook_point(t, "send", VERY_FIRST, log_send);
  loadmod_add_hook_point(t, "web_create", VERY_FIRST, log_create);
  loadmod_add_hook_point(t, "web_delete", VERY_FIRST, log_delete);
  loadmod_add_comp_version(t, 0.1, NULL);
  loadmod_add_comp_version(t, 0.2, NULL);
  loadmod_add_comp_version(t, 0.3, NULL);
}

/* call.c ends here */
