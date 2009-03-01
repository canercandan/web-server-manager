#!/usr/bin/env php
<?php

include_once('functions_es.php');

echo "test socket!\n";

es_connectto('localhost', 4242, 'demo', 'demo');
es_sendto("web_create\n");

$res = explode(' ', trim(es_recvfrom()));
var_dump($res);

es_close();

?>