LKSCTP_TOOLS_DEVEL=/usr/include/netinet/sctp.h

target-y :=
ifneq ($(wildcard $(LKSCTP_TOOLS_DEVEL)),)
  target-y += IPPROTO_SCTP
  target-y += client server
else
  $(warning "WARNING: Maybe install lksctp-tools development package")
endif

CFLAGS += -lsctp
LDFLAGS := $(CFLAGS)

include ../../../template/main.mk

IPPROTO_SCTP: IPPROTO_SCTP.o
client: client.o
server: server.o
