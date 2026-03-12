OUTPUT := .output/

M32 ?= 1

# Include '_start' function
target-asm-y += call-func call-func-ret
target-asm-y += jmp jg jl
target-asm-y += write write-2 write-3

target-asm-std-y += average
target-asm-std-y += echo
target-asm-std-y += fibonacci
target-asm-std-y += power

target-y += factorial_call
target-y += maxofthree_call

factorial_call-objs := ${OUTPUT}factorial.asm.o
maxofthree_call-objs := ${OUTPUT}maxofthree.asm.o
