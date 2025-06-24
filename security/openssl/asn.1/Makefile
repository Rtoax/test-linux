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

CFLAGS :=
# FIXME: I'm too lazy
CFLAGS += -Wno-error=unused-variable
CFLAGS += -Wno-error=unused-but-set-variable
CFLAGS += -Wno-error=pointer-sign
CFLAGS += -Wno-incompatible-pointer-types
CFLAGS += -Wno-error=deprecated-declarations

LDFLAGS += $(shell pkg-config --libs --cflags openssl)

include ../../../template/main.mk

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
