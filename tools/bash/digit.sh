#!/bin/bash

is_digit() {
	grep '^[[:digit:]]*$' <<< "$1" 2>/dev/null || {
		echo "ERROR: $1 is not digit" >&2
		return 1
	}
	return 0
}

is_digit abc || true
is_digit 000
is_digit 123
is_digit -123
is_digit a23 || true

