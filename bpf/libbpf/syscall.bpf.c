/**
 * BPF_PROG_TYPE_SYSCALL
 *
 * Syscall programs can be used to execute syscalls from eBPF.
 *
 * The abstract purpose of the syscall program type is to execute syscalls from
 * eBPF. The initial use case for this program type was to offload some of the
 * work of loader libraries to syscall eBPF programs. The program type can also
 * be used by for "HID-BPF" to register a BPF program as a HID device driver.
 *
 * Syscall programs are never attached to any hook. They can only be executed
 * from the "BPF_PROG_RUN"(alias BPF_PROG_TEST_RUN) syscall command.
 *
 * [1] https://docs.ebpf.io/linux/program-type/BPF_PROG_TYPE_SYSCALL/
 */

// TODO
