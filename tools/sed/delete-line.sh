#!/bin/bash
set -ex

sed '/NAME/d' /etc/os-release
# Delete 1st line if it's whiteline
sed '1{/^$/d}' /etc/os-release
