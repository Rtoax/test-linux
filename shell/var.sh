#!/bin/bash

var=
message="错啦老铁，var没被定义"

echo ${var:+$message}
var=1
echo ${var:+$message}
unset var

echo ${var:-$message}
unset var

echo ${var:=$message}
echo var=$var
unset var

# shell exit here
echo ${var:?$message}

