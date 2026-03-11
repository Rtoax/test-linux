OUTPUT := .output/

M32 ?= 1

# Include '_start' function
target-asm-y += call-func call-func-ret
target-asm-y += jmp jg jl
target-asm-y += write write-2 write-3

target-y += average
target-y += echo
target-y += power
target-y += factorial_call
target-y += maxofthree_call

average-objs := ${OUTPUT}average.asm.o
echo-objs := ${OUTPUT}echo.asm.o
power-objs := ${OUTPUT}power.asm.o
factorial_call-objs := ${OUTPUT}factorial.asm.o
maxofthree_call-objs := ${OUTPUT}maxofthree.asm.o

include main.mk

call-func: ${OUTPUT}call-func.asm.o
call-func-ret: ${OUTPUT}call-func-ret.asm.o
jmp: ${OUTPUT}jmp.asm.o
jg: ${OUTPUT}jg.asm.o
jl: ${OUTPUT}jl.asm.o
write: ${OUTPUT}write.asm.o
write-2: ${OUTPUT}write-2.asm.o
write-3: ${OUTPUT}write-3.asm.o
