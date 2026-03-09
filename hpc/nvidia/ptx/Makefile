OUTPUT := .output/

include nvidia/cuda.mk

target-nvcc-y += laneid
target-nvcc-y += globaltimer

include main.mk

globaltimer: ${OUTPUT}globaltimer.cu.o
laneid: ${OUTPUT}laneid.cu.o
