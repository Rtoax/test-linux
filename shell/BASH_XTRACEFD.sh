#!/bin/bash

set -x

log=a.txt
exec > >(tee ${log}) 2>&1
exec 7> ${log}
BASH_XTRACEFD=7

uname -r
uname -m
uname -a
