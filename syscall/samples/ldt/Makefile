targets :=
ifeq ($(shell uname -m),x86_64)
  targets += get_thread_area
  targets += set_thread_area
  targets += modify_ldt
endif

include ../../../template/main.mk

get_thread_area: get_thread_area.o
set_thread_area: set_thread_area.o
modify_ldt: modify_ldt.o
