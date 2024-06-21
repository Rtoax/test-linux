GO = $(shell which go 2>/dev/null)

TARGETS :=
ifneq ($(wildcard $(GO)),)
TARGETS += hello
TARGETS += io.Copy io.Copy.Pipe io.Copy.Std
TARGETS += fibonacci
TARGETS += pi
#TARGETS += ignition
TARGETS += write
endif

all: ${TARGETS}

${TARGETS}:
	@echo -e "  GO  \033[1;32m$(@)\033[m"
	@$(GO) build $(@).go

clean:
	@echo -e "  CLEAN  \033[1;32mGO\033[m"
	@rm -f ${TARGETS} *.txt
