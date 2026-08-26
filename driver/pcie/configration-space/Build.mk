include helpers.mk

target-y += parse
prog-y += parse.sh

parse-objs := ${PCIE_HELPERS}
