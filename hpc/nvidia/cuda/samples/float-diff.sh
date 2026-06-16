#!/bin/bash
set -e

./float-c nocolor ${@} > float-c.log
./float nocolor ${@} > float.log

diff -up float.log float-c.log
