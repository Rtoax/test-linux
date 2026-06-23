include rpm.mk
include runprog.mk

SPECS := Conflicts.spec

# $1: spec file
define rpmbuild
$(shell ${RUNPROG} -- ${RPMBUILD} -ba --define \"_topdir ${CURDIR}\" ${1})
endef

$(foreach spec, ${SPECS}, \
  $(eval log := $(call rpmbuild, ${spec})))
