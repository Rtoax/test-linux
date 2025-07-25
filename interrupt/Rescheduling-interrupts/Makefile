targets :=
targets += demo-eventfd
ifeq ($(shell uname -m),x86_64)
  targets += demo-select_eventfd
  targets += demo-epoll_eventfd
else ifeq ($(shell uname -m),aarch64)
endif

include ../../template/main.mk

demo-eventfd: demo-eventfd.o common.o
demo-select_eventfd: demo-select_eventfd.o common.o
demo-epoll_eventfd: demo-epoll_eventfd.o common.o
