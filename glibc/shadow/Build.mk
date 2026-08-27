target-y := getspent
target-y += getspnam

prog-y += $(filter-out getspent, ${target-y})

getspent-objs := shadow_helpers.o
getspnam-objs := shadow_helpers.o
