# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk

CC := gcc
LIBPROCFS_DIR := ../../fs/procfs/

TARGETS := dl_iterate_phdr
TARGETS += dl_iterate_phdr-pie
TARGETS += has_shared_object

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -I${LIBPROCFS_DIR}

LDFLAGS :=

CFLAGS_dl_iterate_phdr := -no-pie
CFLAGS_dl_iterate_phdr-pie := -fpie
LDFLAGS_dl_iterate_phdr-pie := -pie

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

dl_iterate_phdr: dl_iterate_phdr.o libtest-linux-procfs.a
dl_iterate_phdr-pie: dl_iterate_phdr-pie.o libtest-linux-procfs.a
has_shared_object: has_shared_object.o

include ${LIBPROCFS_DIR}/procfs-lib-target.mk

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.a
