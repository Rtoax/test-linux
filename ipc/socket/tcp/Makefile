SHELL = bash

sub-dir := simple
sub-dir += select
sub-dir += epoll
sub-dir += poll
sub-dir += splice
sub-dir += ftp
sub-dir += ipv6

TARGETS += tcp-syn-flood

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
all: $(TARGETS) $(sub-dir-build)

tcp-syn-flood: tcp-syn-flood.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f $(TARGETS) *.o

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	@make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	@make -C $(@:.clean=) clean
