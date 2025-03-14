include ../tlbuild.mk


sub-dir := socket
sub-dir += msgqueue
sub-dir += shm
sub-dir += pipe
sub-dir += dbus

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

include ../template/subdir-footer.mk
