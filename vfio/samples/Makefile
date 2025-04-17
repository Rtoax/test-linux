include ../../tlbuild.mk

CC := gcc

TARGETS :=
TARGETS += vfio_region_info

vfio_region_info: vfio_region_info.o

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(Q)$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	$(Q)$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	$(Q)rm -f ${TARGETS} *.o

