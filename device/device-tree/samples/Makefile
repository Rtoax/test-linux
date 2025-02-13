include ../../../tlbuild.mk



TARGETS := helloworld.dtb

build: ${TARGETS}

%.dtb: %.dts
	@echo -e "  CC  \033[32m$(<)\033[m to \033[32m$(@)\033[m"
	dtc -I dts -O dtb -o $(@) $(<) --include ${PWD}

clean:
	rm -f ${TARGETS}
