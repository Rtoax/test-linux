include cestc/lingspeed.mk
include cestc/luca.mk

target-prog-${HAVE_LINGSPEED_GPU} += gpuinfo.sh

subdir-${HAVE_LINGSPEED_GPU} += lingspeed
subdir-${HAVE_LUCA} += luca
