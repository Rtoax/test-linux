LKSCTP_TOOLS_DEVEL=/usr/include/netinet/sctp.h

TARGETS :=
ifneq ($(wildcard $(LKSCTP_TOOLS_DEVEL)),)
  TARGETS += IPPROTO_SCTP
  TARGETS += client server
else
  $(warning "WARNING: Maybe install lksctp-tools development package")
endif

CFLAGS += -lsctp
LDFLAGS := $(CFLAGS)

include ../../../template/main.mk

IPPROTO_SCTP: IPPROTO_SCTP.o
client: client.o
server: server.o
