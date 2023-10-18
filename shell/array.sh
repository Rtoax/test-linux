#!/bin/bash

read_array()
{
	pkgs="a b c"
	read -a arr <<< ${pkgs[@]}
	echo ${arr[@]}
}

read_array
