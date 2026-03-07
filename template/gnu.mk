# SPDX-License-Identifier: GPL-3.0
ifndef _GNU_MK
export _GNU_MK = 1

include ansi.mk

define logo_gnu
@echo -e '${ANSI_BOLD}${ANSI_GREEN}    _-`````-,           ,- `- .${ANSI_RST}'
@echo -e '${ANSI_BOLD}${ANSI_GREEN}  .`   .- - |          | - -.  `.${ANSI_RST}'
@echo -e '${ANSI_BOLD}${ANSI_GREEN} /.`  /                     `.   \ ${ANSI_RST}'
@echo -e '${ANSI_BOLD}${ANSI_GREEN}:/   :      _...   ..._      ``   :${ANSI_RST}'
@echo -e '${ANSI_BOLD}${ANSI_GREEN}::   :     /._ .`:`_.._\.    ||   :${ANSI_RST}'
@echo -e '${ANSI_BOLD}${ANSI_GREEN}::    `._ ./  ,`  :    \ . _.``   .${ANSI_RST}'
@echo -e '${ANSI_BOLD}${ANSI_GREEN}`:.      /   |  -.  \-. \\_      /${ANSI_RST}'
@echo -e '${ANSI_BOLD}${ANSI_GREEN}  \:._ _/  .`   .@)  \@) ` `\ ,.`${ANSI_RST}'
@echo -e '${ANSI_BOLD}${ANSI_GREEN}     _/,--`       .- .\,-.`--`.${ANSI_RST}'
@echo -e '${ANSI_BOLD}${ANSI_GREEN}       ,`/``     (( \ `  )${ANSI_RST}'
@echo -e '${ANSI_BOLD}${ANSI_GREEN}        /`/`  \    `-`  (${ANSI_RST}'
@echo -e '${ANSI_BOLD}${ANSI_GREEN}         `/``  `._,-----`${ANSI_RST}'
@echo -e '${ANSI_BOLD}${ANSI_GREEN}          ``/`    .,---`${ANSI_RST}'
@echo -e '${ANSI_BOLD}${ANSI_GREEN}           ``/`      ;:${ANSI_RST}'
@echo -e '${ANSI_BOLD}${ANSI_GREEN}             ``/``  ``/${ANSI_RST}'
@echo -e '${ANSI_BOLD}${ANSI_GREEN}               ``/``/``${ANSI_RST}'
@echo -e '${ANSI_BOLD}${ANSI_GREEN}                 `/`/`${ANSI_RST}'
@echo -e '${ANSI_BOLD}${ANSI_GREEN}                  `;${ANSI_RST}'
endef

endif
