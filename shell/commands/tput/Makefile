# SPDX-License-Identifier: GPL-3.0
target-shell-y := allcolor.sh

target-post-y := tput_test1

include main.mk

log_color_idx := 0

define _next_color
$(eval log_color_idx := $(shell expr $(log_color_idx) + 1))
$(word $(log_color_idx), $(TPUT_COLORS))
endef

define log_next_color
printf "$(shell tput setaf $(call _next_color))$1$(shell tput sgr0)\n" | tee --append ${LOG_FILE_INFO}
endef

.PHONY: tput_test1
tput_test1:
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
	$(call log_next_color,Test log_next_color)
