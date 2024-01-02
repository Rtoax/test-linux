
TARGETS := clGetPlatformIDs

CC = gcc

CFLAGS :=

LDFLAGS :=
LDLIBS :=

CFLAGS += -DDEBUG -O0 -g
CFLAGS += -lOpenCL
CFLAGS += -DCL_TARGET_OPENCL_VERSION=100

.PHONY: build
build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
clGetPlatformIDs: clGetPlatformIDs.o

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.s *.o *.d
