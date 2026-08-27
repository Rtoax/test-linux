target-y += arg arg-O3

prog-y := optimizers.sh
prog-y += ${target-y}

CFLAGS_arg := -O0
CFLAGS_arg-O3 := -O3
