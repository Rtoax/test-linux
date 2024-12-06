SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


all:
	./uname.sh

test:
clean:
	@echo -e "  CLEAN  \033[1;32m$(@)\033[m"
	${Q}rm -f *.log
