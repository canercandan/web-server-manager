#!/usr/bin/env php
<?php

include_once('functions_es.php');

echo "test socket!\n";

$res = es_connectto('localhost', 4242, 'demo', 'demo');

var_dump($res);

$domains = array(120 => 'google.fr',
		 340 => 'yahoo.com',
		 555 => 'lycos.fr');

/* echo "*** web_create\n"; */

/* foreach ($domains as $key => $value) */
/*   { */
/*     es_sendto("web_create $key $value\n"); */
/*     $res = explode(' ', trim(es_recvfrom())); */
/*     var_dump($res); */
/*   } */

echo "*** web_delete\n";

foreach ($domains as $key => $value)
  {
    es_sendto("web_delete $key\n");
    $res = explode(' ', trim(es_recvfrom()));
    var_dump($res);
  }

es_close();

?>