target-y += a2d_ASN1_OBJECT
target-y += a2i_ASN1_INTEGER
target-y += a2i_ASN1_STRING
#target-y += asc2uni
target-y += ASN1_BIT_STRING_get_bit
target-y += ASN1_d2i_bio
target-y += ASN1_ENUMERATED_get
target-y += ASN1_ENUMERATED_to_BN
target-y += ASN1_i2d_bio
target-y += ASN1_parse_dump
target-y += ASN1_STRING_cmp
target-y += i2a_ASN1_INTEGER
target-y += i2a_ASN1_STRING

# FIXME: I'm too lazy
CFLAGS += -Wno-error=unused-variable
CFLAGS += -Wno-error=unused-but-set-variable
CFLAGS += -Wno-error=pointer-sign
CFLAGS += -Wno-incompatible-pointer-types
CFLAGS += -Wno-error=deprecated-declarations

LDFLAGS += $(shell pkg-config --libs --cflags openssl)
