#!/bin/bash

x86_push_idx()
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

plt_got_idx _GLOBAL_OFFSET_TABLE_
