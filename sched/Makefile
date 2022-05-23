
TARGET:=uninterruptible.out

all:${TARGET}

uninterruptible.out:
	gcc uninterruptible.c -o uninterruptible.out

kill:
	kill $(shell pgrep uninterruptible)

clean:
	rm -f ${TARGET}
