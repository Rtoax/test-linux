#!/bin/bash
# mis-using string comparisons
#
val1=baseball
val2=Baseball
#
if [ $val1 \> $val2 ]; then
	echo "$val1 is greater than $val2"
else
	echo "$val1 is less than $val2"
fi

val1="rongtao"
val2="rongtao"

if [ $val1 = "rongtao" ]; then
	echo "$val1 is equal $val2"
else
	echo "$val1 is not equal $val2"
fi
