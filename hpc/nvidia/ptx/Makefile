OUTPUT := .output/

include nvidia/cuda.mk

target-nvcc-y += laneid

include main.mk

laneid: ${OUTPUT}laneid.cu.o
