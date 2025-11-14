# SPDX-License-Identifier: GPL-3.0
_GNU = 1

ifndef _ANSI
  $(error Not define _ANSI, include ansi.mk)
endif

define gnu_logo
	@echo -e '${ANSI_BOLD}${ANSI_GRE}    _-`````-,           ,- `- .${ANSI_RST}'
	@echo -e '${ANSI_BOLD}${ANSI_GRE}  .`   .- - |          | - -.  `.${ANSI_RST}'
	@echo -e '${ANSI_BOLD}${ANSI_GRE} /.`  /                     `.   \ ${ANSI_RST}'
	@echo -e '${ANSI_BOLD}${ANSI_GRE}:/   :      _...   ..._      ``   :${ANSI_RST}'
	@echo -e '${ANSI_BOLD}${ANSI_GRE}::   :     /._ .`:`_.._\.    ||   :${ANSI_RST}'
	@echo -e '${ANSI_BOLD}${ANSI_GRE}::    `._ ./  ,`  :    \ . _.``   .${ANSI_RST}'
	@echo -e '${ANSI_BOLD}${ANSI_GRE}`:.      /   |  -.  \-. \\_      /${ANSI_RST}'
	@echo -e '${ANSI_BOLD}${ANSI_GRE}  \:._ _/  .`   .@)  \@) ` `\ ,.`${ANSI_RST}'
	@echo -e '${ANSI_BOLD}${ANSI_GRE}     _/,--`       .- .\,-.`--`.${ANSI_RST}'
	@echo -e '${ANSI_BOLD}${ANSI_GRE}       ,`/``     (( \ `  )${ANSI_RST}'
	@echo -e '${ANSI_BOLD}${ANSI_GRE}        /`/`  \    `-`  (${ANSI_RST}'
	@echo -e '${ANSI_BOLD}${ANSI_GRE}         `/``  `._,-----`${ANSI_RST}'
	@echo -e '${ANSI_BOLD}${ANSI_GRE}          ``/`    .,---`${ANSI_RST}'
	@echo -e '${ANSI_BOLD}${ANSI_GRE}           ``/`      ;:${ANSI_RST}'
	@echo -e '${ANSI_BOLD}${ANSI_GRE}             ``/``  ``/${ANSI_RST}'
	@echo -e '${ANSI_BOLD}${ANSI_GRE}               ``/``/``${ANSI_RST}'
	@echo -e '${ANSI_BOLD}${ANSI_GRE}                 `/`/`${ANSI_RST}'
	@echo -e '${ANSI_BOLD}${ANSI_GRE}                  `;${ANSI_RST}'
endef
