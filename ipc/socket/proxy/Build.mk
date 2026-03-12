target-y := eproxy
target-y += proxy2

CFLAGS_eproxy := -I../../../algorithm/list/samples/single-header/
CFLAGS_proxy2 := -DUSE_SPLICE
