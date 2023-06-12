#!/bin/bash

if [[ ! -e /usr/include/asm/unistd_64.h ]]; then
	echo "ERROR: /usr/include/asm/unistd_64.h not exist."
	exit 1
fi

cat >nr.h<<-EOF
#if defined(NR_SYS)
EOF
grep __NR_ /usr/include/asm/unistd_64.h | \
	awk '{print "NR_SYS("$2")"}' \
	>> nr.h
cat >>nr.h<<-EOF
#else
# error "Undefined NR_SYS"
#endif
EOF

