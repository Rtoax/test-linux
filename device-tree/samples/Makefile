
TARGETS := helloworld.dtb

build: ${TARGETS}

%.dtb: %.dts
	@echo -e "Compile  \033[32m$(<)\033[m to \033[32m$(@)\033[m"
	dtc -I dts -O dtb -o $(@) $(<)

clean:
	rm -f ${TARGETS}
