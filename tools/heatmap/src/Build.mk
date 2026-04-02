target-y += heatmap

heatmap-objs := ${OUTPUT}main.o
heatmap-objs += ${OUTPUT}common.o
heatmap-objs += ${OUTPUT}addr.o

CFLAGS += -I.
LDFLAGS += -lm
