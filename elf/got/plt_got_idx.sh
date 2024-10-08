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

plt_got_idx()
{
	local exe=$1

	case $(uname -m) in
	x86_64)
		x86_push_idx ${exe}
		;;
	*)
		echo "ERROR: Not support $(uname -m)" >&2
		exit 1
		;;
	esac
}

plt_got_idx _GLOBAL_OFFSET_TABLE_
