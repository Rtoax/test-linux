TARGETS := main
TARGETS += jl

CFLAGS += -Iinclude
CFLAGS += -O1 -g

include ../../template/main.mk

main: main.o jump_label.o jump_label_x86.o
jl: jl.o
