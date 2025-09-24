#!/bin/bash
set -e

make float-c float

./float-c nocolor > float-c.log
./float nocolor > float.log

diff -up float.log float-c.log
