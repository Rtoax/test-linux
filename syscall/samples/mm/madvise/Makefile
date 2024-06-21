
TARGETS += madvise-MADV_MERGEABLE
TARGETS += madvise-MADV_HUGEPAGE

CC = gcc
CXX = g++

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -Wstrict-prototypes
CFLAGS += -I../../
CFLAGS += -pthread
CFLAGS += -O0

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
madvise-MADV_MERGEABLE: madvise-MADV_MERGEABLE.o
madvise-MADV_HUGEPAGE: madvise-MADV_HUGEPAGE.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.dat

