SHELL = bash

JAVA = $(shell which java 2>/dev/null)
JAVAC = $(shell which javac 2>/dev/null)

TARGETS :=

ifneq ($(JAVAC),)
TARGETS += hello.class
TARGETS += malloc.class
TARGETS += url_GET.class
else
$(warning "Not found javac compiler")
endif

all: $(TARGETS)

hello.class: hello.java
malloc.class: malloc.java
url_GET.class: url_GET.java

$(TARGETS): %:
	@echo -e "  JAVAC  \033[1;32m$(@)\033[m"
	@$(JAVAC) $(^)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	@$(JAVA) hello

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.class
