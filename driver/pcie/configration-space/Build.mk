include helpers.mk

target-y += parse
prog-y += info.sh

parse-objs := ${PCIE_HELPERS}
