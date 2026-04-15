#!/bin/bash
set -e

grep_func() {
	grep ${@}
}

echo aaaAaaa | grep_func -o a
