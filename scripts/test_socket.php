#!/usr/bin/env php
<?php

include_once('functions_es.php');

echo "test socket!\n";

$fp = es_connectto('localhost', 4242, 'demo', 'demo');
fwrite($fp, "create_web_site\n");
es_sendto($fp, "create_web_site\n");
echo es_recvfrom($fp);
es_close($fp);

?>