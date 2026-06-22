include rpm.mk

# $1: spec file
define rpmbuild
$(shell ${RPMBUILD} -ba --define "_topdir $(shell echo $$PWD)" ${1})
endef

$(call rpmbuild,Conflicts.spec)
