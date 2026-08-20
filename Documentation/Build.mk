# SPDX-License-Identifier: GPL-3.0
subdir-y += images

prep-y += htmldocs

prog-y += abbrev.sh
prog-y += abbrev.sh.1
prog-y += abbrev.sh.2
prog-y += history.sh

PROG_ARGS_abbrev.sh.1 := -C --check
PROG_ARGS_abbrev.sh.2 := BPF
