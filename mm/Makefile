sub-dir := rss
sub-dir += cache
sub-dir += hugepage
sub-dir += oom
sub-dir += tcmalloc
sub-dir += jemalloc

TARGETS := virt2phy

CC = gcc

CFLAGS := -DDPDK=1

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: all
all: ${TARGETS} $(sub-dir-build)

virt2phy: virt2phy.o

.PHONY: clean
clean: $(sub-dir-clean)
	rm -f ${TARGETS} *.o

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	make -C $(@:.clean=) clean
