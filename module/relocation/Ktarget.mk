# SPDX-License-Identifier: GPL-3.0
generated_functions.h: generate_code.py
	${Q}./generate_code.py

big-text.h: big-text.sh
	${Q}./big-text.sh
