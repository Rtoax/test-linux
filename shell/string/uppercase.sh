#!/bin/bash
set -e

name=rongTAO

[[ ${name^} != RongTAO ]] && exit 1
[[ ${name,,} != rongtao ]] && exit 1

[[ $(echo ${name} | sed 's/.*/\L&/; s/^./\U&/') != Rongtao ]] && exit 1
[[ $(echo ${name} | awk '{print toupper(substr($0,1,1)) tolower(substr($0,2))}') != Rongtao ]] && exit 1

first=$(echo "$name" | cut -c1 | tr '[:lower:]' '[:upper:]')
rest=$(echo "$name" | cut -c2- | tr '[:upper:]' '[:lower:]')
[[ ${first}${rest} != Rongtao ]] && exit 1

exit 0
