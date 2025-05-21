include ../../tlbuild.mk
include ../../kconfig.mk

sub-dir := samples

TARGETS :=

include ../../template/subdir-header.mk

.PHONY: build
all: $(TARGETS) $(sub-dir-build)

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

include ../../template/subdir-footer.mk
