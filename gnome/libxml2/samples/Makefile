include ../../../tlbuild.mk


TARGETS :=
TARGETS += addchild
TARGETS += parsexml
TARGETS += newformatxml
TARGETS += modifyxml

CC = gcc

LIBXML2_VERSION := libxml-2.0
LIBXML2_LIBS := $(shell pkg-config --libs libxml-2.0)
LIBXML2_CFLAGS := $(shell pkg-config --cflags libxml-2.0)

CFLAGS := -Werror -Wall
CFLAGS += $(LIBXML2_CFLAGS)
CFLAGS += $(LIBXML2_LIBS)

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
addchild: addchild.o
parsexml: parsexml.o
newformatxml: newformatxml.o
modifyxml: modifyxml.o

# FIXME: maybe use BAD_CAST
CFLAGS_addchild := -Wno-error=pointer-sign

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d tmp-*.xml
