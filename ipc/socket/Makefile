include ../../tlbuild.mk

sub-dir := poll
sub-dir += epoll
sub-dir += iovec
sub-dir += proxy
sub-dir += syscall
sub-dir += unix
sub-dir += tcp
sub-dir += sctp
sub-dir += udp
sub-dir += vsock
sub-dir += ipv6

TARGETS :=
TARGETS += sockaddr-size

CC := gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g

include ../../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build) $(TARGETS)
	@echo -e " \033[1;33m Done \033[m"

sockaddr-size: sockaddr-size.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^)

test: ${TARGETS} $(sub-dir-test)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o

include ../../template/subdir-footer.mk
