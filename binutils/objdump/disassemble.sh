#!/bin/bash
set -e

objdump -d --section=.plt /usr/bin/ls

