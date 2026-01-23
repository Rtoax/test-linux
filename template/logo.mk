# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Functions:
# - logo_test_linux()
# - logo_linux_tux()
# - logo_tux()
#
ifndef _LOGO_MK
_LOGO_MK = 1

include ansi.mk

define logo_test_linux
@echo -e "$(1)${GB}88888888${RG}                        ${RGB}  88${RG}${RST}"
@echo -e "$(1)${GB}   88${RG}                      ,d   ${RGB}  88${RG}      88${RST}"
@echo -e "$(1)${GB}   88${RG}                      88   ${RGB}  88${RG}${RST}"
@echo -e "$(1)${GB}   88${RG}  ,adPYba, ,adPYba, MM88MM ${RGB}  88${RG}      88 8b,dYba,  88     88 8b,   db ${RST}"
@echo -e "$(1)${GB}   88${RG} a8P____88 I8<   88   88   ${RGB}  88${RG}      88 88P' '*8a 88     88  'Y,,8' ${RST}"
@echo -e "$(1)${GB}   88${RG} 8PP'''''   '*Yba,    88   ${RGB}  88${RG}      88 88     88 88     88    88(${RST}"
@echo -e "$(1)${GB}   88${RG} '8b,  ,aa aa   ]8I   88,  ${RGB}  88${RG}      88 88     88 '8a, ,a88  ,d68, ${RST}"
@echo -e "$(1)${GB}   88${RG}   *Ybd8*   *YbdP*    *Y88 ${RGB}  8888888${RG} 88 88     88  \"YdP:Y8 8P/   'Y8 ${RST}"
endef

# https://www.ascii-art.de/ascii/jkl/linux.txt
define logo_linux_tux
@echo -e "$(1)                                                               ${BB}#####${RST}"
@echo -e "$(1)                                                              ${BB}#######${RST}"
@echo -e "$(1)                 ${GB}#${RST}                                            ${BB}##${RST}O${BB}#${RST}O${BB}##${RST}"
@echo -e "$(1)${YB}######${RST}          ${GB}###${RST}                                           ${BB}#${RST}${RB}VVVVV${RST}${BB}#${RST}"
@echo -e "$(1)${YB}  ##${RST}             ${GB}#${RST}                                          ${BB}##${RST}  ${RB}VVV${RST}  ${BB}##${RST}"
@echo -e "$(1)${YB}  ##${RST}         ${GB}###${RST}    ${YB}### ####   ###    ###  ##### #####${RST}     ${BB}#${RST}          ${BB}##${RST}"
@echo -e "$(1)${YB}  ##${RST}        ${GB}#  ##${RST}    ${YB}###    ##  ##     ##    ##   ##${RST}      ${BB}#${RST}            ${BB}##${RST}"
@echo -e "$(1)${YB}  ##${RST}       ${GB}#   ##${RST}    ${YB}##     ##  ##     ##      ###${RST}        ${BB}#${RST}            ${BB}###${RST}"
@echo -e "$(1)${YB}  ##${RST}          ${GB}###${RST}    ${YB}##     ##  ##     ##      ###${RST}       ${YB}QQ${RST}${RST}${BB}#${RST}           ${BB}##${RST}${YB}Q${RST}"
@echo -e "$(1)${YB}  ##       #${RST} ${GB}###${RST}     ${YB}##     ##  ##     ##     ## ##${RST}    ${YB}QQQQQQ${RST}${BB}#${RST}       ${BB}#${RST}${YB}QQQQQQ${RST}"
@echo -e "$(1)${YB}  ##      ##${RST} ${GB}### #${RST}   ${YB}##     ##  ###   ###    ##   ##${RST}   ${YB}QQQQQQQ${RST}${BB}#${RST}     ${BB}#${RST}${YB}QQQQQQQ${RST}"
@echo -e "$(1)${YB}############${RST}  ${GB}###${RST}   ${YB}####   ####   #### ### ##### #####${RST}   ${YB}QQQQQ${RST}${BB}#######${RST}${YB}QQQQQ${RST}"
endef

# https://asciiart.website/cat.php?category_id=183
define logo_tux
@echo -e "$(1)                ${BB}.88888888:.${RST}"
@echo -e "$(1)               ${BB}88888888.88888.${RST}"
@echo -e "$(1)             ${BB}.8888888888888888.${RST}"
@echo -e "$(1)             ${BB}888888888888888888${RST}"
@echo -e "$(1)             ${BB}88'${RST} _${BB}'88'${RST}_  ${BB}'88888${RST}"
@echo -e "$(1)             ${BB}88${RST} 88 ${BB}88${RST} 88  ${BB}88888${RST}"
@echo -e "$(1)             ${BB}88_${RST}88${BB}_::_${RST}88${BB}_:88888${RST}"
@echo -e "$(1)             ${BB}88${RST}${RB}:::,::,:::::${RST}${BB}8888${RST}"
@echo -e "$(1)             ${BB}88${RST}${RB}':::::::::''${RST}${BB}8888${RST}"
@echo -e "$(1)            ${BB}.88${RST}  ${RB}'::::'${RST}    ${BB}8:88.${RST}"
@echo -e "$(1)           ${BB}8888${RST}            ${BB}'8:888.${RST}"
@echo -e "$(1)         ${BB}.8888'${RST}             ${BB}'888888.${RST}"
@echo -e "$(1)        ${BB}.8888:${RST}..  .::.  ...${BB}:'8888888:.${RST}"
@echo -e "$(1)       ${BB}.8888.'${RST}     :'     ''::${BB}'88:88888${RST}"
@echo -e "$(1)      ${BB}.8888${RST}        '         ${BB}'.888:8888.${RST}"
@echo -e "$(1)     ${BB}888:8${RST}         .           ${BB}888:88888${RST}"
@echo -e "$(1)   ${BB}.888:88${RST}        .:           ${BB}888:88888:${RST}"
@echo -e "$(1)   ${BB}8888888.${RST}       ::           ${BB}88:888888${RST}"
@echo -e "$(1)   ${BB}'${RST}${YB}.::.${RST}${BB}888.${RST}      ::          ${BB}.88888888${RST}"
@echo -e "$(1)  ${YB}.::::::.${RST}${BB}888.${RST}    ::         ${YB}:::${RST}${BB}'8888'${RST}${YB}.:.${RST}"
@echo -e "$(1) ${YB}::::::::::.${RST}${BB}888${RST}   '         ${YB}.::::::::::::${RST}"
@echo -e "$(1) ${YB}::::::::::::.${RST}${BB}8${RST}    '      ${BB}.:8${RST}${YB}::::::::::::.${RST}"
@echo -e "$(1)${YB}.::::::::::::::.${RST}        ${BB}.:888${RST}${YB}:::::::::::::${RST}"
@echo -e "$(1)${YB}:::::::::::::::${RST}${BB}88:.__..:88888${RST}${YB}:::::::::::'${RST}"
@echo -e "$(1) ${YB}''.:::::::::::${RST}${BB}88888888888.88${RST}${YB}:::::::::'${RST}"
@echo -e "$(1)       ${YB}'':::_:'${RST}${BB} -- '' -'-' ''${RST}${YB}:_::::''${RST}"
endef

endif
