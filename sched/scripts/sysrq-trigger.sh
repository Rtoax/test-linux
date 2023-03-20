#!/bin/bash

# sysrq: Show Blocked State
dmesg_task_stack()
{
	echo w > /proc/sysrq-trigger
}

case $1 in
stack)
	dmesg_task_stack
	;;
*)
	cat <<-END

 stack     - show tasks stack in dmesg

END
	;;
esac
