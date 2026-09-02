target-y += getspent
target-y += getspnam

prog-y += $(filter-out getspent, ${target-y})

PROG_ENVS_getspnam := --maybe-sudo

getspent-objs := shadow_helpers.o
getspnam-objs := shadow_helpers.o
