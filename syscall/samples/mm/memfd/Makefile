target-y += memfd_create
target-y += memfd_create-dup2
target-y += MFD_ALLOW_SEALING
target-y += memfd_secret

memfd_create-objs := memfd_helpers.o
memfd_create-dup2-objs := memfd_helpers.o
MFD_ALLOW_SEALING-objs := memfd_helpers.o
memfd_secret-objs := memfd_helpers.o

CFLAGS += -pthread
CFLAGS += -DTEST_MEMFD=1

include main.mk
