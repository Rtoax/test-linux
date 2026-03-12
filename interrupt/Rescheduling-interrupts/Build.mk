target-y += demo-eventfd
target-${IS_X86_64} += demo-select_eventfd
target-${IS_X86_64} += demo-epoll_eventfd

demo-eventfd-objs := common.o
demo-select_eventfd-objs := common.o
demo-epoll_eventfd-objs := common.o
