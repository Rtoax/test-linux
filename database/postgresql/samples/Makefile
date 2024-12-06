SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS :=
TARGETS += list_tables
TARGETS += PQconnectdb
TARGETS += PQdb
TARGETS += PQexec
TARGETS += PQexecParams
TARGETS += PQfname
TARGETS += PQgetvalue
TARGETS += PQlibVersion
TARGETS += PQnfields
TARGETS += PQntuples
TARGETS += PQpass
TARGETS += PQserverVersion
TARGETS += PQuser
TARGETS += transaction

CC = gcc

CFLAGS :=
LDFLAGS :=

CFLAGS += -lpq
LDFLAGS += -lpq

# Compile nothing if not install libpq.
ifeq ($(wildcard /usr/include/libpq-fe.h),)
  $(warning Not install libpq develope header)
  TARGETS :=
endif

all: ${TARGETS}

list_tables: list_tables.o
PQconnectdb: PQconnectdb.o
PQdb: PQdb.o
PQexec: PQexec.o
PQexecParams: PQexecParams.o
PQfname: PQfname.o
PQgetvalue: PQgetvalue.o
PQlibVersion: PQlibVersion.o
PQnfields: PQnfields.o
PQntuples: PQntuples.o
PQpass: PQpass.o
PQserverVersion: PQserverVersion.o
PQuser: PQuser.o
transaction: transaction.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o
