# SPDX-License-Identifier: GPL-3.0
prog-y += blocksize.sh
prog-y += totalsize.sh

PROG_ARGS_totalsize.sh := /etc/os-release /etc/hosts
