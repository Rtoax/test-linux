# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao

# Black
ANSI_BLK := \033[30m
ANSI_RED := \033[31m
TPUT_RED := $(shell tput setaf 1 2>/dev/null)
ANSI_GRE := \033[32m
TPUT_GRE := $(shell tput setaf 2 2>/dev/null)
ANSI_YEL := \033[33m
TPUT_YEL := $(shell tput setaf 3 2>/dev/null)
ANSI_BLU := \033[34m
TPUT_BLU := $(shell tput setaf 6 2>/dev/null)
ANSI_PUR := \033[35m
ANSI_CYAN := \033[36m
ANSI_DARK_WHITE := \033[37m

ANSI_BRIGHT_BLACK := \033[90m
ANSI_BRIGHT_RED := \033[91m

ANSI_BOLD := \033[1m
ANSI_GRAY := \033[2m
ANSI_ITAL := \033[3m
# Underline
ANSI_UNDL := \033[4m
ANSI_REVE := \033[7m

ANSI_RST := \033[m
TPUT_RST := $(shell tput sgr0 2>/dev/null)

GB := ${ANSI_GRE}${ANSI_BOLD}
RGB := ${ANSI_RST}${ANSI_GRE}${ANSI_BOLD}
RG := ${ANSI_RST}${ANSI_GRE}${ANSI_GRAY}
RST := ${ANSI_RST}

define green
${ANSI_GRE}$1${ANSI_RST}
endef
define red
${ANSI_RED}$1${ANSI_RST}
endef
define bold
${ANSI_BOLD}$1${ANSI_RST}
endef
define yellow
${ANSI_YEL}$1${ANSI_RST}
endef
