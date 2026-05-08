#!/bin/bash
set -e

start=$(date +%s%6N)
sleep 0.123
end=$(date +%s%6N)

expr $(expr ${end} - ${start}) / 1000
