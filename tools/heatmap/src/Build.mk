target-y += heatmap

heatmap-objs := ${OUTPUT}main.o
heatmap-objs += ${OUTPUT}heatmap.o

LDFLAGS += -lm
