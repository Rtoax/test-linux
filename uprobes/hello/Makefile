target-y :=
target-y += hello
target-y += hello-pie

CFLAGS_hello += -no-pie
LDFLAGS_hello += -no-pie
CFLAGS_hello-pie := -fpie
LDFLAGS_hello-pie := -pie

include ../../template/main.mk

hello: hello.o
hello-pie: hello-pie.o
