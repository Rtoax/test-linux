target-y := main
main-objs := sm4_aesni_x4.o sm4.o
CFLAGS := -Og -msse4 -maes
