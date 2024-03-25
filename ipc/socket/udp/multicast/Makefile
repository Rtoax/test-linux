CC := gcc

TARGETS :=
TARGETS += receiver
TARGETS += sender

ALL: $(TARGETS)

receiver: receiver.o common.o
sender: sender.o common.o

clean:
	rm -f ${TARGETS} *.o
