#!/bin/bash
set -e

code=big-text.h
declare -a functions
NUM=100

rm -f ${code}

for ((i = 0; i < NUM; i++))
do
	func=func_stub_${i}
	functions+=( ${func} )

	tput sc
	printf "Gen func ${func} (%ld/%ld)" $i $NUM
	tput rc

	cat>>${code}<<-EOF
	static int __attribute__((optimize("-O0"))) ${func}(void) {
		char volatile buff[1024] = {"Hello World from ${func}\n" \\
			"and this is a big data on stack!!!!!!!!!!!!!!!!!\n" \\
			"$(uname -a)" \\
			"$(hostname)" \\
			"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" \\
			"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" \\
			"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" \\
			"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" \\
			"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" \\
			"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" \\
			"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" \\
		};
		printk("function %s", "${func}");
		printk("buff %s", buff);
		return 0x${functions:10};
	}
	EOF
done

cat>>${code}<<-EOF
static __attribute__((optimize("-O0"))) unsigned long call_big_text(void)
{
	unsigned long volatile count = 0;
EOF

for ((i = 0; i < NUM; i++))
do
	func=${functions[i]}
	tput sc
	printf "Call func ${func} (%ld/%ld)" $i $NUM
	tput rc

	cat>>${code}<<-EOF
	count += ${func}();
	EOF
done

cat>>${code}<<-EOF
	return count;
}
EOF
printf "\n"
