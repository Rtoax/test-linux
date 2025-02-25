#!/bin/bash
set -ex

ld_so=$( which ld.so 2>/dev/null || true )
if [[ -z ${ld_so} ]]; then
	echo "WARNING: Not found ld.so"
	exit 0
fi
ld.so --list /bin/ls
# 可调参数
ld.so --list-tunables
# 诊断
ld.so --list-diagnostics
