#!/bin/bash
# Copyright (C) 2025-2026 Rong Tao. All rights reserved.

if [[ -z ${RED} ]]; then
	readonly RED="\033[31m"
	readonly GREEN="\033[32m"
	readonly YELLOW="\033[33m"
	readonly BLUE="\033[34m"
	readonly PURPLE="\033[35m"

	readonly BOLD="\033[1m"
	readonly GRAY="\033[2m"
	readonly ITALIC="\033[3m"
	readonly UL="\033[4m" # Underline
	readonly REVERSE="\033[7m"

	readonly RST="\033[m"
fi

error() {
	echo -e >&2 "${RED}ERROR: ${@}${RST}"
	exit 1
}

warning() {
	echo -e >&2 "${RED}WARNING: ${@}${RST}"
}

