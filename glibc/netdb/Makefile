TARGETS :=
TARGETS += gai_strerror
TARGETS += getaddrinfo
TARGETS += gethostbyaddr
TARGETS += gethostbyname
TARGETS += hstrerror

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

LDFLAGS :=
LDLIBS :=


.PHONY: build
build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

gai_strerror: gai_strerror.o
getaddrinfo: getaddrinfo.o
gethostbyaddr: gethostbyaddr.o helpers.o
gethostbyname: gethostbyname.o helpers.o
hstrerror: hstrerror.o

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o
