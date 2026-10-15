include cxl.mk
include ndctl.mk

subdir-${HAVE_CXL_DEVICE} += cxl
subdir-y += nvdimm
