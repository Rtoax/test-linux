
TARGETS := hello

CC = nvcc

CFLAGS :=

LDFLAGS :=
LDLIBS :=

CFLAGS += -DDEBUG -O0 -g

.PHONY: build
build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
hello: hello.o

CFLAGS_main.user := -D_MAIN_USER=1
LDFLAGS_main.user :=

%.o: %.cu
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.s *.o *.d
