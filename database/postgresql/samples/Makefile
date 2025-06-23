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

CFLAGS += -lpq
LDFLAGS += -lpq

# Compile nothing if not install libpq.
ifeq ($(wildcard /usr/include/libpq-fe.h),)
  $(warning Not install libpq develope header)
  TARGETS :=
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
