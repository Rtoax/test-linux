include nvidia/cuda.mk
include nvidia/device.mk
include nvidia/nccl.mk

subdir-${HAVE_CUDA} += cuda
subdir-y += driver
subdir-${HAVE_NCCL} += nccl
subdir-${HAVE_NVIDIA_GPU} += nvidia-smi

prog-y += gpuinfo.sh
prog-y += gpuname.sh
