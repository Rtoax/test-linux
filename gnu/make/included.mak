# SPDX-License-Identifier: GPL-3.0

# Any one can include this makefile, this function will return current makefile
# name.
# Note: Deepseek said this feature cannot be implemented.
define current_makefile
$(shell realpath $${0})
endef
$(info current_makefile = $(call current_makefile))

$(info MAKEFILE_LIST = ${MAKEFILE_LIST})
