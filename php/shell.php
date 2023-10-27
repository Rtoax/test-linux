<?php

$cmd = "echo Hello World";
exec($cmd, $log, $status);
echo "$log, $status";
?>