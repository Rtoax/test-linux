target-y += basic-vm
target-y += hello

target-prep-y += ${OUTPUT}hello.s.o.bin
target-prep-y += load-payload01
target-prep-y += load-payload02
target-prep-y += cpuid
target-prep-y += assemly-compiling
target-prep-y += ia32e-paging
target-prep-y += protected-mode-with-paging
target-prep-y += exceptions

hello-objs := ${OUTPUT}kvm_helpers.o
basic-vm-objs := ${OUTPUT}kvm_helpers.o
