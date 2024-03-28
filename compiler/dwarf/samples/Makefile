
TARGETS := hello

CFLAGS := -Werror -Wall
CFLAGS_DBG := -g

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

hello: hello.o

CFLAGS_hello += -Wno-error=unused-variable

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_DBG) $(CFLAGS_$(*)) -o $(@) -c $(<)
	$(CC) $(CFLAGS) $(CFLAGS_DBG) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)
	$(CC) $(CFLAGS)               $(CFLAGS_$(*)) -S $(<) -o $(<:.c=-nodebuginfo.s)
	@echo "--------- show different --------"
	@diff -up $(<:.c=-nodebuginfo.s) $(<:.c=.s) | nl | sed "s|^|$(*): |g" || true

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)
	dwz $(@) -o $(@).dwz

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.s *.dwz
