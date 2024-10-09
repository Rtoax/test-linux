#!/bin/bash
set -e

prog_name=plt_got_idx

elf_file=
# Output gcc -specs format
flag_gcc_spec=
flag_arg=

__x86_push_val()
{
	local exe=$1

	#0000000000401150 <call04@plt>:
	#  401150:	ff 25 3a 2f 00 00    	jmp    *0x2f3a(%rip)
	#  401156:	68 12 00 00 00       	push   $0x12
	#  40115b:	e9 c0 fe ff ff       	jmp    401020 <_init+0x20>
	objdump -d ${exe} | grep '@plt>:' -A 3 \
		| awk '
			BEGIN {
				func_at_plt = "NULL"
			}
			{
				if (match($2, "@plt>:"))
					func_at_plt = $2;
				if ($(NF-1) == "push")
					push_idxs[func_at_plt] = $(NF);
			} END {
				for (f in push_idxs)
					print(f, " ", push_idxs[f])
			}
		' | tr -d '<>:$' | xargs printf "%s %d\n"
}

x86_64_push_idx()
{
	local exe=$1
	__x86_push_val ${exe} | awk '{printf "%s %d\n", $1, $2 + 3}'
}

i386_push_idx()
{
	local exe=$1
	__x86_push_val ${exe} | awk '{printf "%s %d\n", $1, $2 / 8 + 3}'
}

x86_push_idx()
{
	local exe=$1
	if [[ "$(file ${exe} | grep -o 64-bit)" == "64-bit" ]]; then
		x86_64_push_idx ${exe}
	elif [[ "$(file ${exe} | grep -o 32-bit)" == "32-bit" ]]; then
		i386_push_idx ${exe}
	else
		echo "ERROR: Not support ${exe}: $(file ${exe})" >&2
		exit 1
	fi
}

arm64_push_idx()
{
	local exe=$1

	#0000000000400650 <printf@plt>:
	#  400650:	90000110 	adrp	x16, 420000 <__libc_start_main@GLIBC_2.34>
	#  400654:	f9401a11 	ldr	x17, [x16, #48]
	#  400658:	9100c210 	add	x16, x16, #0x30
	#  40065c:	d61f0220 	br	x17
	objdump -d ${exe} | grep '@plt>:' -A 4 \
		| awk '
			BEGIN {
				func_at_plt = "NULL"
			}
			{
				if (match($2, "@plt>:"))
					func_at_plt = $2;
				if (NF > 3 && $(NF-3) == "add")
					add_off[func_at_plt] = $(NF);
			} END {
				for (f in add_off)
					print(f, " ", add_off[f])
			}
		' | tr -d '<>:#' \
		| xargs printf "%s %d\n" \
		| awk '{printf "%s %d\n", $1, $2 / 8 + 7}'
}


plt_got_idx()
{
	local exe=$1

	case $(uname -m) in
	x86_64)
		x86_push_idx ${exe}
		;;
	aarch64)
		arm64_push_idx ${exe}
		;;
	*)
		echo "ERROR: Not support $(uname -m)" >&2
		exit 1
		;;
	esac
}

got_idx()
{
	local exe=$1
	plt_got_idx ${exe} \
		| sed 's/@plt//g' \
		| tr [:lower:] [:upper:] \
		| awk '{printf "GOT_IDX_%s %s\n", $1, $2}'
}

__usage__()
{
	echo -e "
$prog_name [options]

-i, --file         specify elf file
-s, --spec         display gcc spec file format
-a, --arg          display arg format like A=1

-h, --help         show this help information
" | more

	exit ${1-0}
}

TEMP=$(getopt \
	--options i:sah \
	--long file: \
	--long spec \
	--long arg \
	--long help \
	-n ${prog_name} -- "$@")

test $? != 0 && __usage__ 1

eval set -- "$TEMP"

while true; do
	case $1 in
	-i|--file)
		shift
		elf_file=$1
		shift
		;;
	-s|--spec)
		shift
		flag_gcc_spec=YES
		;;
	-a|--arg)
		shift
		flag_arg=YES
		;;
	-h|--help)
		shift
		__usage__
		;;
	--)
		shift
		break
		;;
	esac
done

if [[ ${elf_file} ]]; then
	if [[ ${flag_gcc_spec} ]]; then
		macros=( $(got_idx ${elf_file} | awk '{printf"-D%s=%s ", $1, $2}') )
		cat <<-EOF
		*cc1_options:
		+ ${macros[@]}
		EOF
	elif [[ ${flag_arg} ]]; then
		macros=( $(got_idx ${elf_file} | awk '{printf"%s=%s ", $1, $2}') )
		cat <<-EOF
		${macros[@]}
		EOF
	else
		got_idx ${elf_file}
	fi
else
	echo "ERROR: Need input elf file with -i"
	__usage__ 1
fi
