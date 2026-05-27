include nvidia/device.mk

subdir-y := cuda
subdir-y += driver
subdir-y += nccl
subdir-${HAVE_NVIDIA_GPU} += nvidia-smi

prog-y := gpuinfo.sh
prog-y += gpuname.sh
