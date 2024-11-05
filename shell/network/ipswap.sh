#!/bin/bash

function ip2num() {
	local ip=$1
	local a=$(echo $ip | awk -F '.' '{print $1}')
	local b=$(echo $ip | awk -F '.' '{print $2}')
	local c=$(echo $ip | awk -F '.' '{print $3}')
	local d=$(echo $ip | awk -F '.' '{print $4}')
	echo "$(( (a<<24)+(b<<16)+(c<<8)+d ))"
}

function num2ip() {
	local num=$1
	local a=$((num>>24))
	local b=$((num>>16&0xff))
	local c=$((num>>8&0xff))
	local d=$((num&0xff))
	echo "$a.$b.$c.$d"
}

num2ip $(ip2num 10.170.6.66)
