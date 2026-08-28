#!/bin/bash
# SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
# Copyright (C) 2025-2026 Rong Tao. All rights reserved.

dry_run()
{
	if [[ ${DRY_RUN} ]]; then
		echo >&2 "${@}"
		return 0
	fi

	echo >&2 -e "${BOLD}${GREEN}Startup: $@${RST}"
	eval "${*}"
	echo >&2 -e "${BOLD}${YELLOW}Done: $@${RST}"

	if [[ ! -z ${DRY_RUN_LOG} ]] && [[ -f ${DRY_RUN_LOG} ]]; then
		echo "${@}" | sudo tee --append ${DRY_RUN_LOG}
	fi
}
