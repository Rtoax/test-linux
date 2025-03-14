include ../../../../tlbuild.mk


TARGETS :=
TARGETS += ftpserv
TARGETS += ftpclnt

CC := gcc

ALL: $(TARGETS)

ftpserv: ftpserv.o
ftpclnt: ftpclnt.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^)

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o os-release
