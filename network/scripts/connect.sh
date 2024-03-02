#!/bin/env bpftrace
/**
 * File: connect.bt
 * Author: Rong Tao <rtoax@foxmail.com>
 * Date: 2022.06.08
 *
 * Make sure connect(2) enter/exit even.
 */

tracepoint:syscalls:sys_enter_connect,
tracepoint:syscalls:sys_exit_connect
{
	time("%H:%M:%S ");
	printf("%-16s %-8s %-8d\n", probe, comm, pid);
}
