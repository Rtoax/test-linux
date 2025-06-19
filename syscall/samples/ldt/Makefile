TARGETS :=
ifeq ($(shell uname -m),x86_64)
  TARGETS += get_thread_area
  TARGETS += set_thread_area
  TARGETS += modify_ldt
endif

include ../../../template/main.mk

get_thread_area: get_thread_area.o
set_thread_area: set_thread_area.o
modify_ldt: modify_ldt.o
