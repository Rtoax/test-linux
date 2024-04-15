TARGETS := atomic_test
TARGETS += __sync_synchronize
TARGETS += spin-demo3 spin-demo3-nonlock

CFLAGS :=

all: ${TARGETS}

__sync_synchronize: __sync_synchronize.o
atomic_test: atomic_test.o
spin-demo3: spin-demo3.o
spin-demo3-nonlock: spin-demo3-nonlock.o

CFLAGS += -lpthread
CFLAGS_spin-demo3-nonlock := -DNONLOCK=1

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*))

clean:
	rm -f ${TARGETS} *.o *.s
