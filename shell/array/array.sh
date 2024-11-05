#!/bin/bash

read_array()
{
	pkgs="a b c"
	read -a arr <<< ${pkgs[@]}
	echo ${arr[@]}
}

array_string()
{
	groups=(
		"Server with GUI"
		"Development Tools"
	)

	for str in "${groups[@]}"
	do
		echo $str
	done
}

read_array
array_string
