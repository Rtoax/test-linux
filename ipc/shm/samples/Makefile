CC := gcc

TARGETS :=
TARGETS += reader
TARGETS += writer

ALL: $(TARGETS)

test: $(TARGETS)
	./writer && ./reader

clean:
	rm -f ${TARGETS}
