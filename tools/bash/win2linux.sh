#!/bin/bash
# Replace "\n\r"(^M) to "\n"

function dos2unix_sed()
{
	for f in $@
	do
		# Skip the symbol link and directory
		[[ -L $f ]] && continue
		[[ -d $f ]] && continue
		echo "Swap $f"
		sed -i 's/\r$//' $f
	done
}

function win2linux()
{
	if [[ -e /usr/bin/dos2unix ]]; then
		dos2unix "$@"
	else
		dos2unix_sed "$@"
	fi
}

if [[ $# > 0 ]]; then
	win2linux "$@"
else
	echo "$0 need input files."
fi
