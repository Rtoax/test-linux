targets := pipe-size
targets += pipe
targets += pipe-fork
targets += pipe-broken-pipe shutdown-broken-pipe

CFLAGS += -lpthread

include ../../../template/main.mk

pipe-size: pipe-size.o
pipe: pipe.o
pipe-fork: pipe-fork.o
pipe-broken-pipe: pipe-broken-pipe.o
shutdown-broken-pipe: shutdown-broken-pipe.o
