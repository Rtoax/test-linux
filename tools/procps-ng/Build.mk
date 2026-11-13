# SPDX-License-Identifier: GPL-3.0
include procps-ng.mk

subdir-y += pgrep
subdir-${HAVE_PS} += ps
subdir-${HAVE_PROCPS_NG_DEVEL} += samples
subdir-y += sysctl
