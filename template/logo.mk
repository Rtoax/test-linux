# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
ifndef _LOGO_MK
_LOGO_MK = 1

include ansi.mk

define tl_logo1
@echo >&2 -e "$(1)${GB}88888888${RG}                        ${RGB}  88${RG}${RST}"
@echo >&2 -e "$(1)${GB}   88${RG}                      ,d   ${RGB}  88${RG}      88${RST}"
@echo >&2 -e "$(1)${GB}   88${RG}                      88   ${RGB}  88${RG}${RST}"
@echo >&2 -e "$(1)${GB}   88${RG}  ,adPYba, ,adPYba, MM88MM ${RGB}  88${RG}      88 8b,dYba,  88     88 8b,   db ${RST}"
@echo >&2 -e "$(1)${GB}   88${RG} a8P____88 I8<   88   88   ${RGB}  88${RG}      88 88P' '*8a 88     88  'Y,,8' ${RST}"
@echo >&2 -e "$(1)${GB}   88${RG} 8PP'''''   '*Yba,    88   ${RGB}  88${RG}      88 88     88 88     88    88(${RST}"
@echo >&2 -e "$(1)${GB}   88${RG} '8b,  ,aa aa   ]8I   88,  ${RGB}  88${RG}      88 88     88 '8a, ,a88  ,d68, ${RST}"
@echo >&2 -e "$(1)${GB}   88${RG}   *Ybd8*   *YbdP*    *Y88 ${RGB}  8888888${RG} 88 88     88  \"YdP:Y8 8P/   'Y8 ${RST}"
endef

# https://www.ascii-art.de/ascii/jkl/linux.txt
define tl_linux_logo1
@echo >&2 -e "                                                                 #####"
@echo >&2 -e "                                                                #######"
@echo >&2 -e "                   #                                            ##O#O##"
@echo >&2 -e "  ######          ###                                           #VVVVV#"
@echo >&2 -e "    ##             #                                          ##  VVV  ##"
@echo >&2 -e "    ##         ###    ### ####   ###    ###  ##### #####     #          ##"
@echo >&2 -e "    ##        #  ##    ###    ##  ##     ##    ##   ##      #            ##"
@echo >&2 -e "    ##       #   ##    ##     ##  ##     ##      ###        #            ###"
@echo >&2 -e "    ##          ###    ##     ##  ##     ##      ###       QQ#           ##Q"
@echo >&2 -e "    ##       # ###     ##     ##  ##     ##     ## ##    QQQQQQ#       #QQQQQQ"
@echo >&2 -e "    ##      ## ### #   ##     ##  ###   ###    ##   ##   QQQQQQQ#     #QQQQQQQ"
@echo >&2 -e "  ############  ###   ####   ####   #### ### ##### #####   QQQQQ#######QQQQQ"
endef

endif
