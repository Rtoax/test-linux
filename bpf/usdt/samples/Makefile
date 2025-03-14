include ../../../tlbuild.mk


TARGETS :=
TARGETS += usdt_test
TARGETS += usdt_hello
TARGETS += usdt_inlined
TARGETS += usdt_quoted_probe
TARGETS += usdt_semaphore_test
TARGETS += usdt_sized_args

CC := gcc

build: ${TARGETS}
	@echo -e "CHECK USDT: \033[1;33msudo bpftrace -l usdt:./usdt_xxx:*\033[m"
	@echo -e "TRACING IT: \033[1;33msudo bpftrace -e 'usdt:./usdt_xxx:tracetest:testprobe{printf("x\n");}'\033[m"

usdt_test: usdt_test.o
usdt_hello: usdt_hello.o
usdt_inlined: usdt_inlined.o
usdt_quoted_probe: usdt_quoted_probe.o
usdt_semaphore_test: usdt_semaphore_test.o
usdt_sized_args: usdt_sized_args.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o
