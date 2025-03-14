#
# 2021-08-02	Rong Tao	Create this.
include ../../../tlbuild.mk


TARGETS :=
TARGETS += consumer producer

CFLAGS :=
CFLAGS += -I. -ggdb

ALL: $(TARGETS)

consumer: consumer.o mlinklist.o
producer: producer.o mlinklist.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^)

test: $(TARGETS)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	./producer && ./consumer

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o test.mmap
