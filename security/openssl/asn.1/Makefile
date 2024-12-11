SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS :=
TARGETS += a2d_ASN1_OBJECT
TARGETS += a2i_ASN1_INTEGER
TARGETS += a2i_ASN1_STRING
#TARGETS += asc2uni
TARGETS += ASN1_BIT_STRING_get_bit
TARGETS += ASN1_d2i_bio
TARGETS += ASN1_ENUMERATED_get
TARGETS += ASN1_ENUMERATED_to_BN
TARGETS += ASN1_i2d_bio
TARGETS += ASN1_parse_dump
TARGETS += ASN1_STRING_cmp
TARGETS += i2a_ASN1_INTEGER
TARGETS += i2a_ASN1_STRING

CC = gcc

LDFLAGS :=
LDLIBS :=

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g -ggdb
CFLAGS +=$(shell pkg-config --libs --cflags openssl)
# FIXME: I'm too lazy
CFLAGS += -Wno-error=unused-variable
CFLAGS += -Wno-error=unused-but-set-variable
CFLAGS += -Wno-error=pointer-sign
CFLAGS += -Wno-incompatible-pointer-types
CFLAGS += -Wno-error=deprecated-declarations

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
a2d_ASN1_OBJECT: a2d_ASN1_OBJECT.o
a2i_ASN1_INTEGER: a2i_ASN1_INTEGER.o
a2i_ASN1_STRING: a2i_ASN1_STRING.o
asc2uni: asc2uni.o
ASN1_BIT_STRING_get_bit: ASN1_BIT_STRING_get_bit.o
ASN1_d2i_bio: ASN1_d2i_bio.o
ASN1_ENUMERATED_get: ASN1_ENUMERATED_get.o
ASN1_ENUMERATED_to_BN: ASN1_ENUMERATED_to_BN.o
ASN1_i2d_bio: ASN1_i2d_bio.o
ASN1_parse_dump: ASN1_parse_dump.o
ASN1_STRING_cmp: ASN1_STRING_cmp.o
i2a_ASN1_INTEGER: i2a_ASN1_INTEGER.o
i2a_ASN1_STRING: i2a_ASN1_STRING.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.cer *.pem
