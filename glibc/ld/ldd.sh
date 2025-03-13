#!/bin/bash
set -ex

# on fedora41 /usr/bin/ld.so -> ../lib64/ld-linux-x86-64.so.2
ld_so=$( which ld.so 2>/dev/null || true )
[[ -z ${ld_so} ]] && ld_so=$(ldconfig -p | awk '{print $NF}' | \
				grep ld-linux- | head -1)

if [[ -z ${ld_so} ]]; then
	echo "WARNING: Not found ld.so"
	exit 0
fi

#${ld_so} --list /bin/ls

# 可调参数
# could grep rtld
[[ "$(${ld_so} 2>&1 | grep list-tunables)" ]] && ${ld_so} --list-tunables
# 诊断
[[ "$(${ld_so} 2>&1 | grep list-diagnostics)" ]] && ${ld_so} --list-diagnostics

true
