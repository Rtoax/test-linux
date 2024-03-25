CC := gcc

TARGETS :=
TARGETS += receiver
TARGETS += sender

ALL: $(TARGETS)

receiver: receiver.o
sender: sender.o

clean:
	rm -f ${TARGETS} *.o
