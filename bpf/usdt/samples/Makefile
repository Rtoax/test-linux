
TARGETS= \
	usdt_test.out \
	usdt_hello.out \
	usdt_inlined.out \
	usdt_quoted_probe.out \
	usdt_semaphore_test.out \
	usdt_sized_args.out

build: ${TARGETS}

%.out: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1;31m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(<)

clean:
	rm -f ${TARGETS} *.o
