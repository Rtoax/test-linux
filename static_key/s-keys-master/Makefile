include ../../tlbuild.mk


TARGETS := main
TARGETS += jl

CFLAGS += -Iinclude
CFLAGS += -O1 -g

.PHONY: all
all: $(TARGETS)

main: main.o jump_label.o jump_label_x86.o
jl: jl.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.s
