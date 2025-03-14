include ../../tlbuild.mk


TARGETS :=
TARGETS += opendir
TARGETS += readdir
TARGETS += telldir
TARGETS += seekdir
TARGETS += rewinddir
TARGETS += scandir
TARGETS += fdopendir
# Demos
TARGETS += listdir
TARGETS += remove_dir

CC := gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g

ifdef M32
  CFLAGS += -m32 -DM32=1
  LDFLAGS += -m32
  $(info Compile 32bit ELF)
endif

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"
	@mkdir -p a.dir/a/b/c/d/e
	@touch a.dir/{a,b,c,d,e}.txt

# Add more object.o file
opendir: opendir.o
readdir: readdir.o
telldir: telldir.o
seekdir: seekdir.o
rewinddir: rewinddir.o
scandir: scandir.o
fdopendir: fdopendir.o
listdir: listdir.o
remove_dir: remove_dir.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d
	${Q}rm -rf a.dir
