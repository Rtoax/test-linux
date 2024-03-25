sub-dir := make
sub-dir += gnupg

TARGETS := __GNUC__

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: $(sub-dir-build) ${TARGETS}

__GNUC__: __GNUC__.o

.PHONY: clean
clean: $(sub-dir-clean)
	rm -rf ${TARGETS} *.o

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	make -C $(@:.clean=) clean
