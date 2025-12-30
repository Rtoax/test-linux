OUTPUT := .output/

target-y := usdt_test
target-y += usdt_hello
target-y += usdt_inlined
target-y += usdt_quoted_probe
target-y += usdt_semaphore_test
target-y += usdt_sized_args
target-y += libbpf

target-post-y := help

include main.mk

help:
	@echo -e "CHECK USDT: \033[1;33msudo bpftrace -l usdt:./usdt_xxx:*\033[m"
	@echo -e "TRACING IT: \033[1;33msudo bpftrace -e 'usdt:./usdt_xxx:tracetest:testprobe{printf("x\n");}'\033[m"

usdt_test: ${OUTPUT}usdt_test.o
usdt_hello: ${OUTPUT}usdt_hello.o
usdt_inlined: ${OUTPUT}usdt_inlined.o
usdt_quoted_probe: ${OUTPUT}usdt_quoted_probe.o
usdt_semaphore_test: ${OUTPUT}usdt_semaphore_test.o
usdt_sized_args: ${OUTPUT}usdt_sized_args.o
libbpf: ${OUTPUT}libbpf.o
