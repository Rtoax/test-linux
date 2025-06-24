include ../../../tlbuild.mk

TARGETS :=
TARGETS += bignum
TARGETS += md5 md5_evp

CC := gcc

LDFLAGS :=

CFLAGS :=
CFLAGS += -I../macro/
CFLAGS += -DDEBUG -O0 -g -ggdb
CFLAGS +=$(shell pkg-config --libs --cflags openssl)

# error: ‘MD5_Init’ is deprecated: Since OpenSSL 3.0
CFLAGS_md5 :=  -Wno-error=deprecated-declarations

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

bignum: bignum.o
md5: md5.o
md5_evp: md5_evp.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.cer *.pem
