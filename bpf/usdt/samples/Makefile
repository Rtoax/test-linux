targets :=
targets += usdt_test
targets += usdt_hello
targets += usdt_inlined
targets += usdt_quoted_probe
targets += usdt_semaphore_test
targets += usdt_sized_args

targets-post := help

include ../../../template/main.mk

help:
	@echo -e "CHECK USDT: \033[1;33msudo bpftrace -l usdt:./usdt_xxx:*\033[m"
	@echo -e "TRACING IT: \033[1;33msudo bpftrace -e 'usdt:./usdt_xxx:tracetest:testprobe{printf("x\n");}'\033[m"

usdt_test: usdt_test.o
usdt_hello: usdt_hello.o
usdt_inlined: usdt_inlined.o
usdt_quoted_probe: usdt_quoted_probe.o
usdt_semaphore_test: usdt_semaphore_test.o
usdt_sized_args: usdt_sized_args.o
