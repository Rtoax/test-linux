#!/bin/bash
set -e

pid=self

cat /proc/${pid}/environ | tr '\0' '\n'

MY_NAME='Rong Tao' cat /proc/${pid}/environ | tr '\0' '\n'

NOT_EXIST___="Set in $0" ./environ.py
./environ.py
