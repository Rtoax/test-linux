TARGETS :=
TARGETS += parsexml

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
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
parsexml: parsexml.o

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
