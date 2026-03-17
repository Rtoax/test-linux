# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Functions:
# - attach_xdp()
# - detach_xdp()
#
# - attach_xdp_with_ip()
# - detach_xdp_with_ip()
#
ifndef _BPF_XDP_MK
_BPF_XDP_MK = 1

include sudo.mk
include bpf/bpf.mk
include bpf/bpftool.mk

# Attach XDP to network interface, the 'xdp' could be change to one of `xdpdrv`
# `xdpgeneric`, `xdpoffload`.
#
# $1: network interface, like 'eth0'
# $2: object bpf file
# $3: bpf program name
define attach_xdp
${SUDO} ${BPFTOOL} prog load ${2} ${BPFFS}/${3} && \
${SUDO} ${BPFTOOL} net attach xdp pinned ${BPFFS}/${3} dev ${1}
endef

# $1: network interface, like 'eth0'
# $2: bpf program name
define detach_xdp
${SUDO} ${BPFTOOL} net detach xdp dev ${1} && ${SUDO} rm -f ${BPFFS}/${2}
endef

# $1: network interface, like 'eth0'
# $2: object bpf file
# $3: section name
define attach_xdp_with_ip
${SUDO} ip link set dev ${1} xdp obj ${2} sec ${3}
endef

# $1: network interface, like 'eth0'
define detach_xdp_with_ip
${SUDO} ip link set dev ${1} xdp off
endef

endif
