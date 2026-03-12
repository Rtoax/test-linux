include nvidia/device.mk

subdir-y := cuda
subdir-y += driver
subdir-y += nccl
subdir-${HAVE_NVIDIA_GPU} += nvidia-smi

target-prog-y := gpuinfo.sh
target-prog-y += gpuname.sh
