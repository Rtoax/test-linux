CC := gcc

TARGETS :=
TARGETS += reader
TARGETS += writer

ALL: $(TARGETS)

reader: reader.o
writer: writer.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: $(TARGETS)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	./writer && ./reader

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o
