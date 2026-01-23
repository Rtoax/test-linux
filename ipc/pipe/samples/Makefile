target-y := pipe-size
target-y += pipe
target-y += pipe-fork
target-y += pipe-broken-pipe shutdown-broken-pipe

LDFLAGS += -lpthread

include main.mk

pipe-size: pipe-size.o
pipe: pipe.o
pipe-fork: pipe-fork.o
pipe-broken-pipe: pipe-broken-pipe.o
shutdown-broken-pipe: shutdown-broken-pipe.o
