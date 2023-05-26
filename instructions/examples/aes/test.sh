#!/bin/bash

openssl_tests=(aes-128-cbc aes-128-ecb aes-256-cbc aes-256-ecb)

# With AES
#type             16 bytes     64 bytes    256 bytes   1024 bytes   8192 bytes  16384 bytes
#AES-128-CBC    1091562.54k  1626622.42k  1648401.29k  1714771.29k  1679105.20k  1697398.78k
#AES-128-ECB    1091401.36k  3612145.09k  6487938.91k  7067147.26k  7191444.46k  7262060.54k
#AES-256-CBC     994681.97k  1229926.34k  1241505.88k  1229722.97k  1234211.10k  1202192.38k
#AES-256-ECB     972128.20k  3242117.31k  4640739.92k  5023514.97k  5062814.38k  5146976.06k

for t in ${openssl_tests[@]}
do
	openssl speed -evp $t
done
