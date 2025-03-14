include ../tlbuild.mk


sub-dir := block

TARGETS :=
TARGETS += cpu_dma_latency
TARGETS += random

CC := gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build) ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

cpu_dma_latency: cpu_dma_latency.o
random: random.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS} $(sub-dir-test)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d

include ../template/subdir-footer.mk
