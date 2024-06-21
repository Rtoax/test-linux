TARGETS :=
TARGETS += hello.class

all: $(TARGETS)

hello.class: hello.java

$(TARGETS): %:
	@echo -e "LD   \033[1;32m$(@)\033[m"
	javac $(^)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"
	java hello

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.class
