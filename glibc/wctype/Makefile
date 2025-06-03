TARGETS := wchar_t
TARGETS += iswctype
TARGETS += wcstol
TARGETS += demo-1

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread

include ../../template/main.mk

iswctype: iswctype.o
wchar_t: wchar_t.o
wcstol: wcstol.o
demo-1: demo-1.o
