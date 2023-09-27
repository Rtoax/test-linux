#!/bin/bash

line="a b c"

printf "%-20s = %s\n" line  "$line"
printf "%-20s = %s\n" '${line// /}' "${line// /}"
printf "%-20s = %s\n" '${line// }'  "${line// }"
