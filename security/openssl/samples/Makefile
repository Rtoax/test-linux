targets :=
targets += bignum
targets += md5 md5_evp

CFLAGS :=
CFLAGS += -I../macro/

LDFLAGS +=$(shell pkg-config --libs --cflags openssl)

# error: ‘MD5_Init’ is deprecated: Since OpenSSL 3.0
CFLAGS_md5 :=  -Wno-error=deprecated-declarations

include ../../../template/main.mk

bignum: bignum.o
md5: md5.o
md5_evp: md5_evp.o
