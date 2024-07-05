RUSTC = $(shell which rustc 2>/dev/null)

TARGETS :=
ifneq ($(RUSTC),)
TARGETS += data-type
TARGETS += hello
TARGETS += threads
else
$(warning "Not found rustc compiler")
endif

all: $(TARGETS)

data-type: data-type.rs
hello: hello.rs
threads: threads.rs

$(TARGETS): %:
	@echo -e "  RUSTC  \033[1;32m$(@)\033[m"
	@$(RUSTC) -o $(@) $(^)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS}
