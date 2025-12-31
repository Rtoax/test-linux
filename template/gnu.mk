# SPDX-License-Identifier: GPL-3.0
_GNU_MK = 1

include ansi.mk

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
