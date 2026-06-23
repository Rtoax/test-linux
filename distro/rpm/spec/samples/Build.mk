include rpm.mk
include runprog.mk

# $1: spec file
define rpmbuild
$(shell ${RUNPROG} -- ${RPMBUILD} -ba --define \"_topdir ${CURDIR}\" ${1})
endef

$(call rpmbuild,Conflicts.spec)
