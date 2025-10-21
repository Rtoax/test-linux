target-y :=
target-y += demo-eventfd
ifeq ($(shell uname -m),x86_64)
  target-y += demo-select_eventfd
  target-y += demo-epoll_eventfd
else ifeq ($(shell uname -m),aarch64)
endif

include ../../template/main.mk

demo-eventfd: demo-eventfd.o common.o
demo-select_eventfd: demo-select_eventfd.o common.o
demo-epoll_eventfd: demo-epoll_eventfd.o common.o
