#!/bin/bash

set -euo pipefail


handle_failed_cmd()
{
	touch /root/tmp || {
		ret_code=$?
		if [[ ${ret_code} -eq 1 ]]; then
			echo Failed.
			return ${ret_code}
		fi
	}
}

handle_failed_cmd || true

