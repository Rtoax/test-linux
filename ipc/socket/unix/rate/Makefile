CC := gcc

TARGETS :=
TARGETS += server
TARGETS += client

ALL: $(TARGETS)

server: server.o common.o
client: client.o common.o

clean:
	rm -f ${TARGETS} *.o
