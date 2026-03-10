include arch.mk

target-${IS_X86_64} += main

LDFLAGS += -Wl,-Tld-alternative.lds
ifneq ($(shell ld --help | grep -o no-warn-rwx-segments),)
  LDFLAGS += -Wl,--no-warn-rwx-segments
endif

include main.mk
