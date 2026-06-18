# SPDX-License-Identifier: GPL-3.0
target-bpf-y := classifier.bpf.o

post-y := help

IF := lo
$(warning "Specify IF=[Interface] like IF=lo")
