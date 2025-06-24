TARGETS := eproxy
TARGETS += proxy2

CFLAGS_eproxy := -I../../../algorithm/list/samples/single-header/
CFLAGS_proxy2 := -DUSE_SPLICE

include ../../../template/main.mk

eproxy: eproxy.o
proxy2: proxy2.o
