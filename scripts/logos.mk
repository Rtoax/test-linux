# SPDX-License-Identifier: GPL-3.0
# Black
ANSI_BLK := \033[30m
ANSI_RED := \033[31m
ANSI_GRE := \033[32m
ANSI_YEL := \033[33m
ANSI_BLU := \033[34m
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
RST := ${ANSI_RST}

GB := ${ANSI_GRE}${ANSI_BOLD}
RGB := ${ANSI_RST}${ANSI_GRE}${ANSI_BOLD}
RG := ${ANSI_RST}${ANSI_GRE}${ANSI_GRAY}

define tl_ascii_logo1
	@echo >&2 -e "$(1)${GB}88888888${RG}                        ${RGB}  88${RG}${RST}"
	@echo >&2 -e "$(1)${GB}   88${RG}                      ,d   ${RGB}  88${RG}      88${RST}"
	@echo >&2 -e "$(1)${GB}   88${RG}                      88   ${RGB}  88${RG}${RST}"
	@echo >&2 -e "$(1)${GB}   88${RG}  ,adPYba, ,adPYba, MM88MM ${RGB}  88${RG}      88 8b,dYba,  88     88 8b,   db ${RST}"
	@echo >&2 -e "$(1)${GB}   88${RG} a8P____88 I8<   88   88   ${RGB}  88${RG}      88 88P' '*8a 88     88  'Y,,8' ${RST}"
	@echo >&2 -e "$(1)${GB}   88${RG} 8PP'''''   '*Yba,    88   ${RGB}  88${RG}      88 88     88 88     88    88(${RST}"
	@echo >&2 -e "$(1)${GB}   88${RG} '8b,  ,aa aa   ]8I   88,  ${RGB}  88${RG}      88 88     88 '8a, ,a88  ,d68, ${RST}"
	@echo >&2 -e "$(1)${GB}   88${RG}   *Ybd8*   *YbdP*    *Y88 ${RGB}  8888888${RG} 88 88     88  \"YdP:Y8 8P/   'Y8 ${RST}"
endef

