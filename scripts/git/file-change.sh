#!/bin/bash

from_commit=54feea9d059b
to_comit=fb40e1052905

git log ${from_commit}...${to_comit} --name-only | \
	grep -v -e '^commit ' -e '^Author:' -e '^Date:' -e '^Merge:' | \
	grep ^[a-zA-Z0-9]
