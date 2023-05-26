#!/bin/bash

support=$(lscpu | grep -o ' aes ')

if [[ ! -z $support ]]; then
	echo "Support AES"
else
	echo "Unsupport AES"
fi
