#!/bin/bash
set -e

ELF=$1
if [[ -z ${ELF} ]]; then
	ELF=hello
fi

run() {
	echo -e "\033[1;32m$ cuobjdump ${@}\033[m"
	eval cuobjdump ${@}
}

run --version
run --help
run --all-fatbin ${ELF}
run --dump-elf -elf ${ELF}
run --dump-sass -sass ${ELF}
run --dump-elf-symbols -symbols ${ELF}
run --dump-ptx -ptx ${ELF}
run --dump-resource-usage -res-usage ${ELF}

run --list-elf ${ELF}
run --list-ptx ${ELF}
run --sort-functions ${ELF}
