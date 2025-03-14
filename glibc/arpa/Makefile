include ../../tlbuild.mk


MAKE_SUB_ARGS :=

sub-dir := inet

include ../../template/subdir-header.mk

ifdef M32
  MAKE_SUB_ARGS += M32=1
endif

.PHONY: build
build: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

include ../../template/subdir-footer.mk
