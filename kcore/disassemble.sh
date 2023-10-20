#!/bin/bash
set -e

ksym=schedule

kaddr=( $(sudo grep -i " ${ksym}$" /proc/kallsyms) )
[[ -z "${kaddr}" ]] && echo "ERROR: Not found ${ksym}" && exit 1

gdb_script=$(mktemp --dry-run tmp-XXXXXX.gdb)

cat >>${gdb_script}<<-EOF
x/120i 0x${kaddr}
quit
EOF

sudo gdb -q -c /proc/kcore < ${gdb_script}

rm -f ${gdb_script}
