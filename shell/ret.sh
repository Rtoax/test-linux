#!/bin/bash

handle_failed_cmd()
{
	touch /root/tmp || {
		ret_code=$?
		if [[ ${ret_code} -eq 1 ]]; then
			echo Failed.
			exit ${ret_code}
		fi
	}
}

handle_failed_cmd

