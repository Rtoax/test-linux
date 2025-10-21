target-y :=
target-y += io_uring-cat
target-y += io_uring-cat-liburing
target-y += io_uring-multi-reqs
target-y += io_uring-web-server
target-y += ordinary-cat
target-y += link-cp
target-y += io_uring-test

LDFLAGS := -luring

include ../../template/main.mk

io_uring-cat: io_uring-cat.o
io_uring-cat-liburing: io_uring-cat-liburing.o
io_uring-multi-reqs: io_uring-multi-reqs.o
io_uring-web-server: io_uring-web-server.o
ordinary-cat: ordinary-cat.o
link-cp: link-cp.o
io_uring-test: io_uring-test.o
