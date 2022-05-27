#!/bin/bash
# Guest OS stress test
# Rong Tao <rongtao@cestc.cn>

OUTPUT_FILE=data.out

###############################################################################
# TEST dd
dd_output_()
{
	dd if=/dev/random of=$OUTPUT_FILE bs=1M count=100
}
dd_input_()
{
	test -f $OUTPUT_FILE && dd if=$OUTPUT_FILE of=/dev/null bs=1M count=100
}
dd_loop_()
{
	echo "Test dd, hit ctrl-c to end."
	while true
	do
		dd_output_ 2>/dev/null
		dd_input_ 2>/dev/null
	done
}

###############################################################################
mkdir_cd_rmdir_()
{
	dir=`mktemp -u /tmp/test____dirXXXXX`
	mkdir -p $dir
	cd $dir
	cd - >/dev/null
	rmdir $dir
}
neg_dentry_()
{
	# access no exist directory
	cd `mktemp -u /tmp/test____dirXXXXX` 2>/dev/null
}
dentry_loop_()
{
	echo "Test dentry, hit ctrl-c to end."
	while :
	do
		mkdir_cd_rmdir_
		neg_dentry_
	done
}

##
###############################################################################
# Set all test here.
#
test_list=(dd_input_ dd_output_ neg_dentry_ mkdir_cd_rmdir_)
test_num=${#test_list[@]}

###############################################################################
# TEST random
get_random_()
{
	echo `expr $RANDOM % $test_num`
}
random_loop_()
{
	echo "Test all, hit ctrl-c to end."
	for ((i=0;i<$test_num;i++))
	do
		echo ${test_list[$i]}
	done
	while :
	do
		${test_list[`get_random_`]} 2>/dev/null
	done
}

###############################################################################
signal_handler()
{
	echo "Catch SIG"
	rm -f $OUTPUT_FILE
	rm -rf /tmp/test____dir*
	exit 0
}

###############################################################################
# __usage__
usage()
{
cat<<'EOF'

usage guest-stress [OPT]

[OPT]
          dd	- Write/Read a file to/from disk.
      dentry	- Generate/Access/Remove dentry.
         ALL	- Random test all above.

 All test is RUNNING FOREVER, hit ctrl-C to end.
EOF
	exit ${1-0}
}

trap "echo Goodbye..." EXIT
trap "signal_handler" SIGINT

###############################################################################
# __main__
case $1 in
dd)
	dd_loop_
	;;
dentry)
	dentry_loop_
	;;
ALL)
	random_loop_
	;;
-h|--help|*)
	usage
	;;
esac
