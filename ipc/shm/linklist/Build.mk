target-y += consumer producer

consumer-objs := mlinklist.o
producer-objs := mlinklist.o

CFLAGS += -I. -ggdb
