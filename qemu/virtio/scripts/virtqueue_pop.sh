#!/bin/env bpftrace
/**
 * File: virtqueue_pop.bt
 * Author: Rong Tao
 * Date: 2022.06.19
 *
 */
BEGIN
{
	printf("Tracing virtqueue_pop, hit ctrl-c to end.\n");
	printf("%-8s %-8s %-8s %-8s\n", "TIME", "PID", "COMM", "PROBE");
}

/**
 * virtqueue_pop: Get data from virtqueue
 * virtqueue_push: Write data to 'Used Ring'
 *
 * for example:
 * virtio_balloon_handle_output()
 * {
 *   for (;;) {
 *     virtqueue_pop();
 *     virtqueue_push();
 *     virtio_notify();
 *   }
 * }
 */
uprobe:/usr/libexec/qemu-kvm:virtqueue_pop
{
	$virtqueue_elemsize = arg1;
	time("%H:%M:%S ");
	printf("%-8d %-8s %-8s %-8d\n", pid, comm, func, $virtqueue_elemsize);
}

uprobe:/usr/libexec/qemu-kvm:virtqueue_push
{
	$elem = arg1;
	$offset = arg2;
	time("%H:%M:%S ");
	printf("%-8d %-8s %-8s %-8d %-8d\n", pid, comm, func, $elem, $offset);
}

END
{
	printf("Bye.\n");
}
