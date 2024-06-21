
TARGETS := dev

TARGETS_LIBS := libdev.so
TARGETS_LIBS += libdev.so.1
TARGETS_LIBS += libdev_hack.so

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

LDFLAGS :=
LDLIBS :=

CFLAGS += -DDEBUG -O0 -g

CFLAGS_dev := -ldev
LDFLAGS_dev := libdev.so


.PHONY: build
build: ${TARGETS_LIBS} ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"
	@echo -e "Running ./run.sh to testing."

# Add more object.o file
libdev.so: libdev.o
dev: dev.o

%.o: %.c
	@echo -e "CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	LD_LIBRARY_PATH=$(shell pwd) $(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

%.so: %.c
	@echo -e "CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	LD_LIBRARY_PATH=$(shell pwd) $(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(<) -shared -fpic

%.so.1: %.so
	@echo -e "CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	mv $(<) $(@)
	ln -s $(@) $(<)

$(TARGETS): %:
	@echo -e "LD   \033[1;32m$(@)\033[m"
	LD_LIBRARY_PATH=$(shell pwd) $(CC) $(CFLAGS) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS} ${TARGETS_LIBS}
	@echo -e "Test   \033[1;32m$(@)\033[m"
	./run.sh

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} ${TARGETS_LIBS} *.o *.so
	@rm -rf rootfs.out
