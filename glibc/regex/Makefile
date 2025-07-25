targets :=
targets += regcomp
targets += re_search
targets += re_match
targets += email
targets += getprocessruntime-regex
targets += printf-format-arg-split
targets += tr069

CFLAGS :=
CFLAGS += -D__USE_GNU=1

# TODO: I don't know why `implicit declaration of function`
CFLAGS_re_search := -Wno-error=implicit-function-declaration
CFLAGS_re_match := -Wno-error=implicit-function-declaration

include ../../template/main.mk

regcomp: regcomp.o
re_search: re_search.o
re_match: re_match.o
email: email.o
getprocessruntime-regex: getprocessruntime-regex.o
printf-format-arg-split: printf-format-arg-split.o
tr069: tr069.o
