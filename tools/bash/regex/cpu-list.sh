#!/bin/bash

total_nlines=`cat cpu-list.txt | wc -l`
match_lines=`cat cpu-list.txt | grep -E "^([0-9]\\w*[,|-])*[0-9]\\w*$"`
match_nlines=`cat cpu-list.txt | grep -E "^([0-9]\\w*[,|-])*[0-9]\\w*$" | wc -l`

echo "Total $total_nlines lines, $match_nlines matched, list:"
echo "$match_lines"
