target-y :=
target-y += list_tables
target-y += PQconnectdb
target-y += PQdb
target-y += PQexec
target-y += PQexecParams
target-y += PQfname
target-y += PQgetvalue
target-y += PQlibVersion
target-y += PQnfields
target-y += PQntuples
target-y += PQpass
target-y += PQserverVersion
target-y += PQuser
target-y += transaction

CFLAGS += -lpq
LDFLAGS += -lpq

# Compile nothing if not install libpq.
ifeq ($(wildcard /usr/include/libpq-fe.h),)
  $(warning Not install libpq develope header)
  target-y :=
endif

include ../../../template/main.mk

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
