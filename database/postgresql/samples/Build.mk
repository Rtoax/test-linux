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

LDFLAGS += -lpq
