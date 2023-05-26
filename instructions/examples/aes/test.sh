#!/bin/bash

openssl_tests=(aes-128-cbc aes-128-ecb aes-256-cbc aes-256-ecb)

for t in ${openssl_tests[@]}
do
	openssl speed -evp $t
done
