include ../tlbuild.mk


sub-dir :=
sub-dir += glib
sub-dir += gtk
sub-dir += libxml2/samples/

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

include ../template/subdir-footer.mk
