OUTPUT := .output/

targets-hipcc := parallel

obj-fatbin := parallel.hip_fatbin parallel.hipFatBinSegment

targets-post := $(patsubst %,${OUTPUT}%,$(obj-fatbin))

include ../../../../template/main.mk

parallel: ${OUTPUT}parallel.hip.o
