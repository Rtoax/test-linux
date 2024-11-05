SHELL = bash

.PHONY: test
test:
	@echo -e "  TEST  \033[1;32m$(@)\033[m"
	./swap-two-words.sh
	./gsub.sh

clean:
	@echo -e "  CLEAN  \033[1;32m$(@)\033[m"
	@rm -f *.log
