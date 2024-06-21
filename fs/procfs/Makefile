sub-dir := process

TARGETS :=
TARGETS += self
TARGETS += auxv
TARGETS += stat
TARGETS += statm

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: ${TARGETS} $(sub-dir-build)
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
self: self.o
auxv: auxv.o
stat: stat.o
statm: statm.o

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(@)\033[m"
	./self

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	make -C $(@:.clean=) clean
