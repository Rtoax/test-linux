include helpers.mk

target-y := truncate
target-y += ftruncate

truncate-objs := ${C_HELPERS}
ftruncate-objs := ${C_HELPERS}
