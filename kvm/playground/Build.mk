ASMFLAGS_NO_DEFAULT_ELF64 = 1

target-y += basic-vm
target-y += hello
target-y += load-payload01
target-y += load-payload02
target-y += cpuid
target-y += exceptions
target-y += protected-mode-with-paging
target-y += ia32e-paging

target-prep-y += ${OUTPUT}a16.asm.o
target-prep-y += ${OUTPUT}a32.asm.o
target-prep-y += ${OUTPUT}a64.asm.o


target-prep-y += ${OUTPUT}hello.s.o.bin
target-prep-y += ${OUTPUT}load-payload01-program.asm.o
target-prep-y += ${OUTPUT}load-payload02-program.asm.o
target-prep-y += ${OUTPUT}cpuid-program.asm.o
target-prep-y += ${OUTPUT}exceptions-a.asm.o
target-prep-y += ${OUTPUT}exceptions-handler.asm.o
target-prep-y += ${OUTPUT}protected-mode-with-paging-a.asm.o
target-prep-y += ${OUTPUT}protected-mode-with-paging-b.asm.o
target-prep-y += ${OUTPUT}protected-mode-with-paging-c.asm.o
target-prep-y += ${OUTPUT}ia32e-paging-a.asm.o
target-prep-y += ${OUTPUT}ia32e-paging-b.asm.o

hello-objs := ${OUTPUT}kvm_helpers.o
basic-vm-objs := ${OUTPUT}kvm_helpers.o
load-payload01-objs := ${OUTPUT}kvm_helpers.o
load-payload01-objs += ${OUTPUT}load-payload01-payload.asm.o
load-payload02-objs := ${OUTPUT}kvm_helpers.o
cpuid-objs := ${OUTPUT}kvm_helpers.o
cpuid-objs += ${OUTPUT}cpuid-payload.asm.o
exceptions-objs := ${OUTPUT}kvm_helpers.o
protected-mode-with-paging-objs := ${OUTPUT}kvm_helpers.o
ia32e-paging-objs := ${OUTPUT}kvm_helpers.o

ASMFLAGS_load-payload01-payload := -felf64
ASMFLAGS_cpuid-payload := -felf64
