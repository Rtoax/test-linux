target-y += bignum
target-y += md5 md5_evp

CFLAGS += -I../macro/

LDFLAGS +=$(shell pkg-config --libs --cflags openssl)

# error: ‘MD5_Init’ is deprecated: Since OpenSSL 3.0
CFLAGS_md5 := -Wno-error=deprecated-declarations
