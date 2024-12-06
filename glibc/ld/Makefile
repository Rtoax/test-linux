SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


.PHONY: all
all:
	@echo -e " \033[1;33m SUBDIR build \033[m"
	./ldd.sh
.PHONY: clean
clean:
	@echo -e " \033[1;33m SUBDIR clean \033[m"
