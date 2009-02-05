<?php
/* functions_es.php --- 
 * 
 * Filename: functions_es.php
 * Description: 
 * Author: Caner Candan
 * Maintainer: 
 * Created: Thu Feb  5 15:18:11 2009 (+0200)
 * Version: 
 * Last-Updated: Thu Feb  5 15:45:04 2009 (+0200)
 *           By: Caner Candan
 *     Update #: 7
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

function	es_connectto($ip, $port)
{
  if (($fp = stream_socket_client('tcp://' . $ip . ':' . $port, $errno, $errstr, 30)) == 0)
    {
      echo "$errstr ($errno)\n";
      exit(-1);
    }
  return ($fp);
}

function	es_sendto($fp, $mesg)
{
  fwrite($fp, $mesg);
}

function	es_recvfrom($fp)
{
  if (!feof($fp))
    return (fgets($fp, 1024));
  return ("");
}

function	es_close($fp)
{
  fclose($fp);
}

/* functions_es.php ends here */

?>