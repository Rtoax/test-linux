# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - FFMPEG=[/usr/bin/ffmpeg]
# - HAVE_FFMPEG=[y|n]
#
ifndef _FFMPEG_MK
_FFMPEG_MK = 1

include define.mk

$(call find_cmd_and_def,ffmpeg)

endif # end of _FFMPEG_MK
