target-y += heatmap

heatmap-objs := main.o
heatmap-objs += heatmap.o

CFLAGS += -I../../../libs/
LDFLAGS += -lm
