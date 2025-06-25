TARGETS :=
TARGETS += io_uring-cat
TARGETS += io_uring-cat-liburing
TARGETS += io_uring-multi-reqs
TARGETS += io_uring-web-server
TARGETS += ordinary-cat
TARGETS += link-cp
TARGETS += io_uring-test

LDFLAGS := -luring

include ../../template/main.mk

io_uring-cat: io_uring-cat.o
io_uring-cat-liburing: io_uring-cat-liburing.o
io_uring-multi-reqs: io_uring-multi-reqs.o
io_uring-web-server: io_uring-web-server.o
ordinary-cat: ordinary-cat.o
link-cp: link-cp.o
io_uring-test: io_uring-test.o
