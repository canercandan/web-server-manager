<?php
/* functions_es.php --- 
 * 
 * Filename: functions_es.php
 * Description: 
 * Author: Caner Candan
 * Maintainer: 
 * Created: Thu Feb  5 15:18:11 2009 (+0200)
 * Version: 
 * Last-Updated: Wed Mar  4 08:36:36 2009 (+0200)
 *           By: Caner Candan
 *     Update #: 63
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

define('FP', 'fp');

$es_arr = array();

function	es_connectto($ip, $port, $login, $passwd)
{
  global $es_arr;

  $es_arr = array();

  if (($es_arr[FP] = stream_socket_client("tcp://$ip:$port", $errno, $errstr)) == 0)
    {
      echo "$errstr ($errno)\n";
      exit(-1);
    }
  stream_set_timeout($es_arr[FP], 5);
  es_sendto("login $login $passwd\n");
  if (($res = es_recvfrom()) == "login ko\n")
    {
      var_dump($res);
      exit(-1);
    }
  return ($res);
}

function	es_sendto($mesg)
{
  global $es_arr;

  fwrite($es_arr[FP], $mesg);
}

function	es_recvfrom()
{
  global $es_arr;

  if (!feof($es_arr[FP]))
    return (fgets($es_arr[FP], 1024));
  return ('');
}

function	es_close()
{
  global $es_arr;

  es_sendto("logout\n");
  if (es_recvfrom() == "logout ko\n")
    exit(-1);
  fclose($es_arr[FP]);
}

/* functions_es.php ends here */

?>