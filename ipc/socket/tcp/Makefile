include ../../../tlbuild.mk


sub-dir := simple
sub-dir += select
sub-dir += epoll
sub-dir += poll
sub-dir += splice
sub-dir += ftp
sub-dir += ipv6

TARGETS += tcp-syn-flood

include ../../../template/subdir-header.mk

.PHONY: build
all: $(TARGETS) $(sub-dir-build)

tcp-syn-flood: tcp-syn-flood.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f $(TARGETS) *.o

include ../../../template/subdir-footer.mk
