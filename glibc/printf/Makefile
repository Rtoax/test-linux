targets :=
targets += parse_printf_format
targets += register_printf_function
targets += register_printf_specifier

CFLAGS :=
CFLAGS_register_printf_function := -Wno-error=deprecated-declarations

include ../../template/main.mk

parse_printf_format: parse_printf_format.o
register_printf_function: register_printf_function.o
register_printf_specifier: register_printf_specifier.o
