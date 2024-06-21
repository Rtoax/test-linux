
TARGETS += data-type
TARGETS += hello
TARGETS += threads

all: $(TARGETS)

data-type: data-type.rs
hello: hello.rs
threads: threads.rs

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	rustc -o $(@) $(^)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS}
