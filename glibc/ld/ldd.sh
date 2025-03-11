#!/bin/bash
set -ex

# on fedora41 /usr/bin/ld.so -> ../lib64/ld-linux-x86-64.so.2
ld_so=$( which ld.so 2>/dev/null || true )
[[ -z ${ld_so} ]] && ld_so=$(ldconfig -p | awk '{print $NF}')

if [[ -z ${ld_so} ]]; then
	echo "WARNING: Not found ld.so"
	exit 0
fi

${ld_so} --list /bin/ls

# 可调参数
${ld_so} --list-tunables
# 诊断
${ld_so} --list-diagnostics
