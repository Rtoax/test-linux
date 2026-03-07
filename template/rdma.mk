# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Input definitions:
#
# Output definitions:
#
ifndef _RDMA_MK
export _RDMA_MK = 1

include define.mk

$(call check_file_and_def,/usr/include/infiniband/ib.h,HAVE_INFINIBAND_IB_H)
$(call check_file_and_def,/usr/include/rdma/rsocket.h,HAVE_RDMA_RSOCKET_H)

endif
