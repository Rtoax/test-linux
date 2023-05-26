#!/bin/bash

openssl_tests=(aes-128-cbc aes-128-ecb aes-256-cbc aes-256-ecb)

# Without AES
#type             16 bytes     64 bytes    256 bytes   1024 bytes   8192 bytes  16384 bytes
#AES-128-CBC     373239.36k   409797.67k   451122.35k   467302.91k   473513.98k   465711.09k
#AES-128-ECB     389699.18k   449418.84k   478088.65k   483042.65k   487969.22k   486517.13k
#AES-256-CBC     286292.63k   322083.98k   322705.21k   322951.11k   342346.15k   335335.00k
#AES-256-ECB     287030.38k   332503.38k   343178.45k   344112.81k   343110.55k   349823.06k

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
