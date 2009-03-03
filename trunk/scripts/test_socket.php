#!/usr/bin/env php
<?php

include_once('functions_es.php');

echo "test socket!\n";

es_connectto('localhost', 4242, 'demo', 'demo');

$domains = array('google.fr', 'yahoo.com', 'lycos.fr');
$ids = array();

foreach ($domains as $value)
  {
    es_sendto("web_create $value\n");
    list($cmd, $ids[$value]) = explode(' ', trim(es_recvfrom()));
  }

var_dump($ids);

foreach ($ids as $key => $value)
  {
    es_sendto("web_delete $value\n");
    $res = explode(' ', trim(es_recvfrom()));
    var_dump($res);
  }

es_close();

?>