# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Input definitions:
# - ANSI_NONE
#
# Exports:
#
ifndef _ANSI_MK
_ANSI_MK = 1

ANSI_BLACK := \033[30m
ANSI_RED := \033[31m
TPUT_RED := $(shell tput setaf 1 2>/dev/null)
ANSI_GREEN := \033[32m
TPUT_GREEN := $(shell tput setaf 2 2>/dev/null)
ANSI_YELLOW := \033[33m
TPUT_YELLOW := $(shell tput setaf 3 2>/dev/null)
ANSI_BLUE := \033[34m
TPUT_BLUE := $(shell tput setaf 6 2>/dev/null)
ANSI_PURPLE := \033[35m
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

TPUT_COLORS := $(shell seq 0 1 $(shell tput colors))

ifdef ANSI_NONE
  ANSI_BLACK :=
  ANSI_RED :=
  TPUT_RED :=
  ANSI_GREEN :=
  TPUT_GREEN :=
  ANSI_YELLOW :=
  TPUT_YELLOW :=
  ANSI_BLUE :=
  TPUT_BLUE :=
  ANSI_PURPLE :=
  ANSI_CYAN :=
  ANSI_DARK_WHITE :=
  ANSI_BRIGHT_BLACK :=
  ANSI_BRIGHT_RED :=
  ANSI_BOLD :=
  ANSI_GRAY :=
  ANSI_ITAL :=
  ANSI_UNDL :=
  ANSI_REVE :=
  ANSI_RST :=
  TPUT_RST :=
  TPUT_COLORS :=
endif

BB := ${ANSI_BLACK}${ANSI_BOLD}
BBR := ${ANSI_BLACK}${ANSI_BOLD}${ANSI_REVE}
CYB := ${ANSI_CYAN}${ANSI_BOLD}
GB := ${ANSI_GREEN}${ANSI_BOLD}
RB := ${ANSI_RED}${ANSI_BOLD}
RBR := ${ANSI_RED}${ANSI_BOLD}${ANSI_REVE}
YB := ${ANSI_YELLOW}${ANSI_BOLD}
YBR := ${ANSI_YELLOW}${ANSI_BOLD}${ANSI_REVE}
RGB := ${ANSI_RST}${ANSI_GREEN}${ANSI_BOLD}
RG := ${ANSI_RST}${ANSI_GREEN}${ANSI_GRAY}
RST := ${ANSI_RST}

define green
${ANSI_GREEN}${1}${ANSI_RST}
endef
define bgreen
${ANSI_BOLD}${ANSI_GREEN}${1}${ANSI_RST}
endef
define red
${ANSI_RED}${1}${ANSI_RST}
endef
define yellow
${ANSI_YELLOW}${1}${ANSI_RST}
endef
define byellow
${ANSI_BOLD}${ANSI_YELLOW}${1}${ANSI_RST}
endef
define bold
${ANSI_BOLD}${1}${ANSI_RST}
endef

endif
