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

include main.mk

average: ${OUTPUT}average.asm.o
echo: ${OUTPUT}echo.asm.o
fibonacci: ${OUTPUT}fibonacci.asm.o
power: ${OUTPUT}power.asm.o
call-func: ${OUTPUT}call-func.asm.o
call-func-ret: ${OUTPUT}call-func-ret.asm.o
jmp: ${OUTPUT}jmp.asm.o
jg: ${OUTPUT}jg.asm.o
jl: ${OUTPUT}jl.asm.o
write: ${OUTPUT}write.asm.o
write-2: ${OUTPUT}write-2.asm.o
write-3: ${OUTPUT}write-3.asm.o
