sub-dir := annobin
sub-dir += linker
sub-dir += __atomic
sub-dir += __attribute__
sub-dir += __builtin_
sub-dir += dwarf
sub-dir += foption
sub-dir += LD_PRELOAD
sub-dir += openmp
sub-dir += pragma
sub-dir += reloc
sub-dir += __sync

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	make -C $(@:.clean=) clean
