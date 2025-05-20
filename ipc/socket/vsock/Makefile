include ../../../tlbuild.mk
include ../../../kconfig.mk

sub-dir := samples

TARGETS :=
TARGETS += vsock

include ../../../template/subdir-header.mk

.PHONY: build
all: $(TARGETS) $(sub-dir-build)

vsock_helpers.o: vsock_helpers.h
vsock: vsock.o vsock_helpers.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^)

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f $(TARGETS) *.o

include ../../../template/subdir-footer.mk
