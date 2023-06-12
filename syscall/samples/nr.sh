#!/bin/bash

unistd=

if [[ -e /usr/include/asm/unistd_64.h ]]; then
	unistd=/usr/include/asm/unistd_64.h
elif [[ -e /usr/include/asm-generic/unistd.h ]]; then
	unistd=/usr/include/asm-generic/unistd.h
fi

if [[ -z ${unistd} ]]; then
	echo "ERROR: ${unistd} not exist."
	exit 1
fi

cat >nr.h<<-EOF
#if defined(NR_SYS)
EOF
for n in $(
grep 'define __NR_' ${unistd} | \
	awk '{print $2}' | \
	grep -v '[{|)|(|,|;|:]')
do
	cat >>nr.h<<-EOF
	#if defined($n)
	NR_SYS($n)
	#endif
	EOF
done >> nr.h
cat >>nr.h<<-EOF
#else
# error "Undefined NR_SYS"
#endif
EOF

