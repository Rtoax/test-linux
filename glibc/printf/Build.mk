include glibc.mk

target-y += parse_printf_format
target-$(call glibc_gt,2,43) += register_printf_function
target-y += register_printf_specifier

prog-y += ${target-y}

CFLAGS_register_printf_function := -Wno-error=deprecated-declarations
