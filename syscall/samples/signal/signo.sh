#!/bin/bash

set -e

output_hdr=sig.h

signo_generic=(
	$(cat /usr/include/bits/signum-generic.h | \
		tr '\t' ' ' | \
		grep 'define SIG' | \
		grep SIG_ -v | \
		awk '{print $2}')
)

signo_arch=(
	$(cat /usr/include/bits/signum-arch.h | \
		tr '\t' ' ' | \
		grep 'define SIG' | \
		grep SIG_ -v | \
		awk '{print $2}')
)

signos=(
	${signo_generic[@]}
	${signo_arch[@]}
)

cat >${output_hdr}<<-EOF
#if defined(NR_SIG)
EOF

for s in ${signos[@]}
do
	cat >>${output_hdr}<<-EOF
	#if defined($s)
	NR_SIG($s)
	#endif
	EOF
done

cat >>${output_hdr}<<-EOF
#else
# error "Undefined NR_SIG"
#endif
EOF

