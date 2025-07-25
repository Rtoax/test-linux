targets :=
targets += memfd_create
targets += memfd_create-dup2
targets += MFD_ALLOW_SEALING
targets += memfd_secret

CFLAGS :=
CFLAGS += -pthread
CFLAGS += -DTEST_MEMFD=1

include ../../../../template/main.mk

memfd_create: memfd_create.o memfd_helpers.o
memfd_create-dup2: memfd_create-dup2.o memfd_helpers.o
MFD_ALLOW_SEALING: MFD_ALLOW_SEALING.o memfd_helpers.o
memfd_secret: memfd_secret.o memfd_helpers.o
