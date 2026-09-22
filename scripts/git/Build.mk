# SPDX-License-Identifier: GPL-3.0
include git.mk

LAST_TAG := $(shell ${GIT} describe --tags --abbrev=0)

prog-y += archive.sh
prog-y += commit-message-stat.sh
prog-y += commit-message-stat.sh.1
prog-y += commit-message-stat.sh.2
prog-y += commit-message-stat.sh.3
prog-y += file-change.sh
prog-y += uncommitted-files.sh
prog-y += version.sh

PROG_ARGS_commit-message-stat.sh.1 := v2.4.6-Kappa v2.4.7-Lamada
PROG_ARGS_commit-message-stat.sh.2 := v2.4.6-Kappa ${LAST_TAG}
PROG_ARGS_commit-message-stat.sh.3 := ${LAST_TAG} HEAD
