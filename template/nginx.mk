# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - NGINX=[/usr/bin/nginx]
# - HAVE_NGINX=[y|n]
#
ifndef _NGINX_MK
_NGINX_MK = 1

include define.mk

$(call find_cmd_and_def,nginx)

endif # end of _NGINX_MK
