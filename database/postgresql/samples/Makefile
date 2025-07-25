targets :=
targets += list_tables
targets += PQconnectdb
targets += PQdb
targets += PQexec
targets += PQexecParams
targets += PQfname
targets += PQgetvalue
targets += PQlibVersion
targets += PQnfields
targets += PQntuples
targets += PQpass
targets += PQserverVersion
targets += PQuser
targets += transaction

CFLAGS += -lpq
LDFLAGS += -lpq

# Compile nothing if not install libpq.
ifeq ($(wildcard /usr/include/libpq-fe.h),)
  $(warning Not install libpq develope header)
  targets :=
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
