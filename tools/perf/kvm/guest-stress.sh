#!/bin/bash
# Guest OS stress test

OUTPUT_FILE=data.out

# TEST dd
dd_()
{
	while true
	do
		dd if=/dev/zero of=$OUTPUT_FILE bs=1M count=100
	done
}

signal_handler()
{
	echo "Catch SIG"
	rm -f $OUTPUT_FILE
	exit 0
}

# __usage__
usage()
{
cat<<'EOF'
usage guest-stress [OPT]

[OPT]
  dd	- write a file to disk.

 All test is RUNNING FOREVER, hit ctrl-C to end.
EOF
	exit ${1-0}
}

trap "echo Goodbye..." EXIT
trap "signal_handler" SIGINT

# __main__
case $1 in
dd)
	dd_
	;;
*)
	usage
	;;
esac
