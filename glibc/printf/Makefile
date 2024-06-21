TARGETS :=
TARGETS += parse_printf_format
TARGETS += register_printf_function
TARGETS += register_printf_specifier

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

parse_printf_format: parse_printf_format.o
register_printf_function: register_printf_function.o
register_printf_specifier: register_printf_specifier.o

CFLAGS_register_printf_function := -Wno-error=deprecated-declarations

%.o: %.c
	@echo -e "CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "LD   \033[1;32m$(@)\033[m"
	$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o

