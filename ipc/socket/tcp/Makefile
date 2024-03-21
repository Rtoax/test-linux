sub-dir := simple
sub-dir := select

TARGETS += tcp-syn-flood

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
all: $(TARGETS) $(sub-dir-build)

tcp-syn-flood: tcp-syn-flood.o

.PHONY: clean
clean: $(sub-dir-clean)
	rm -f $(TARGETS) *.o

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	make -C $(@:.clean=) clean
