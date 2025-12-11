#!/bin/env bpftrace
/**
 * File: virtqueue_fill.bt
 * Author: Rong Tao
 * Date: 2022.06.19
 *
 */
BEGIN
{
	printf("Tracing virtqueue_fill, hit ctrl-c to end.\n");
	printf("%-8s %-8s %-8s %-8s %-8s\n",
			"TIME", "PID", "COMM", "LEN", "IDX");
}

uprobe:/usr/libexec/qemu-kvm:virtqueue_fill
{
	$len = arg2;
	$idx = arg3;
	time("%H:%M:%S ");
	printf("%-8d %-8s %-8d %-8d\n", pid, comm, $len, $idx);
}

END
{
	printf("Bye.\n");
}
