LKSCTP_TOOLS_DEVEL=/usr/include/netinet/sctp.h

ifneq ($(wildcard $(LKSCTP_TOOLS_DEVEL)),)
  target-y += IPPROTO_SCTP
  target-y += client server
else
  $(warning "WARNING: Maybe install lksctp-tools development package")
endif

CFLAGS += -lsctp
LDFLAGS := $(CFLAGS)

include main.mk
