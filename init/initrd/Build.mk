# SPDX-License-Identifier: GPL-3.0
include dracut.mk

subdir-${HAVE_DRACUT} += dracut
subdir-y += minimal
subdir-y += rpmbuild
