#!/bin/bash

errnos_base=(
	$(cat /usr/include/asm-generic/errno-base.h | tr '\t' ' ' | grep 'define E' | awk '{print $2}')
)
errnos=(
	$(cat /usr/include/asm-generic/errno.h | tr '\t' ' ' | grep 'define E' | awk '{print $2}')
)

file=errors.h

cat >${file}<<-EOF
#if defined(NR_ERRNO)
EOF

for n in ${errnos_base[@]} ${errnos[@]}
do
	cat >>${file}<<-EOF
	NR_ERRNO($n)
	EOF
done
cat >>${file}<<-EOF
#else
# error "Undefined NR_ERRNO"
#endif
EOF

