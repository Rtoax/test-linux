# man gcc: GCC depresses SSEx instructions when -mavx is used
target-y += sum

$(foreach i, 1 2 3 4 5 6 7, \
  $(eval target-y += sum.${i}) \
  $(eval sum.${i}-objs := ${OUTPUT}sum.${i}.o) \
)

CFLAGS_sum.1 := -msse
CFLAGS_sum.2 := -msse2
CFLAGS_sum.3 := -msse3
CFLAGS_sum.4 := -mssse3
CFLAGS_sum.5 := -msse4.1
CFLAGS_sum.6 := -msse4.2
CFLAGS_sum.7 := -msse4

CFLAGS += -O1
CFLAGS += -ftree-vectorize
CFLAGS += -DTYPE_FLOAT
