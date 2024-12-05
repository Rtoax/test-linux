# SPDX-License-Identifier: GPL-3.0
SHELL = bash

.PHONY: test
test:
	@echo -e "  TEST  \033[1;32m$(@)\033[m"
	./ipv4.sh
	./tab.sh

clean:
	@echo -e "  CLEAN  \033[1;32m$(@)\033[m"
	@rm -f *.log
