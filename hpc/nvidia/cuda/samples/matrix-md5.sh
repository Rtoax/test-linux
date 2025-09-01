#!/bin/bash
# Usage: [TXT=1] ./matrix-md5.sh
set -e

DATAS_MD5_FILE_BIN=(
d89606d5e485fff33fb295c6b5f2d974  matrix-c-k1000_m1000_n1000.bin
db4121f6cb258573aacf608d75e89e12  matrix-c-k100_m100_n100.bin
c3312f95aff9dfdeb8bfde5bc692dea2  matrix-c-k200_m200_n200.bin
40f12a81ca614f7f6122595140e5e89a  matrix-c-k300_m300_n300.bin
0d0262b210dec31b68eb0e56f683d2c6  matrix-c-k400_m400_n400.bin
c42ca9f2f331960dc0bcfc13dc34cd43  matrix-c-k500_m500_n500.bin
737b6716210e973074fd9581b827b2a0  matrix-c-k600_m600_n600.bin
2f65c29fa103f83db1308d9d0c9faadf  matrix-c-k700_m700_n700.bin
28bbbaabef850ca0544a1d1150a8f682  matrix-c-k800_m800_n800.bin
f93cbdecf242f096b0190d5746a15933  matrix-c-k900_m900_n900.bin
c1c37b5889cc9ffe32d89889502d246d  matrix-c-double-k1000_m1000_n1000.bin
e236c83f877bb81a80a22e2debeb8659  matrix-c-double-k100_m100_n100.bin
cfdb9e909b9ec30f8c3a476902080a9f  matrix-c-double-k200_m200_n200.bin
31524cb6ad131ffc1bf08d2480946637  matrix-c-double-k300_m300_n300.bin
4940600445f44e3245c76b27d8e0e0b2  matrix-c-double-k400_m400_n400.bin
71df988253b835226409be99fe3a81f1  matrix-c-double-k500_m500_n500.bin
65d5c2768b0b03d71c4be24a1ca8669b  matrix-c-double-k600_m600_n600.bin
fed78c0aea252faed8c8eb99804b321f  matrix-c-double-k700_m700_n700.bin
18b7a82e52077e4011d2c9d3a39d7d33  matrix-c-double-k800_m800_n800.bin
3a3571bd2277c32ee3994956035051a8  matrix-c-double-k900_m900_n900.bin
629bbfbc540ecf9b8614c3bade229f0c  matrix-k1000_m1000_n1000.bin
7e5ade454b857d4d9be5e53b6c7a1225  matrix-k100_m100_n100.bin
c233b4cc0022c678d5cb6a9ea0c456d6  matrix-k200_m200_n200.bin
2882c5f1ff6c747b0a35e85b95c4057d  matrix-k300_m300_n300.bin
18a77e80a97373af5478090d0369d9c5  matrix-k400_m400_n400.bin
1ee287d585d229c9c17f84c7011d55a5  matrix-k500_m500_n500.bin
93f206bd99fb13075dee77cd98485202  matrix-k600_m600_n600.bin
c64e35c886346e397885c4c17a7174fc  matrix-k700_m700_n700.bin
109596205a435e9dafa91d29b905962f  matrix-k800_m800_n800.bin
da851493a22d75385b8e50ead6869e2d  matrix-k900_m900_n900.bin
)

DATAS_MD5_FILE_TXT=(
0cf9b2292c4a24d41b9ccaea5a29571f  matrix-c-k1000_m1000_n1000.log
d04dcf17d1135ccb6458fb1efd605159  matrix-c-k100_m100_n100.log
bbb8a1074f68b5c9735ae6c77ec0bdf4  matrix-c-k200_m200_n200.log
05de7226992bda26ba86317efb1a8e47  matrix-c-k300_m300_n300.log
7937cda9d14d7bc584ce0f7c0aa47850  matrix-c-k400_m400_n400.log
9bde03b383a4fefae62821af2515c783  matrix-c-k500_m500_n500.log
9abc774828ddb102b748dd11f6ee7707  matrix-c-k600_m600_n600.log
ad5a9e526b90639a7794f75e4e1b8f65  matrix-c-k700_m700_n700.log
f5902134613d73f204cf7b5f1f858beb  matrix-c-k800_m800_n800.log
4e6be1c7a41e3cab390e518eb764fbbe  matrix-c-k900_m900_n900.log
cf17414f95852dbe1b2478633d5edc6a  matrix-k1000_m1000_n1000.log
05c6a3006b74f07df9e94d5145e37891  matrix-k100_m100_n100.log
abf5abb1fb2363ce998aafd112d4adc2  matrix-k200_m200_n200.log
d375ad416950f24302792003560df260  matrix-k300_m300_n300.log
67cb3132b590074d034be0b072910c7b  matrix-k400_m400_n400.log
1cca9b04dd8b72dbec4a6e04b4a764a2  matrix-k500_m500_n500.log
a2ead9faf905c7e779f2de5e4c0a9851  matrix-k600_m600_n600.log
1e56b5a58830ac120787e49d61b359d3  matrix-k700_m700_n700.log
8b2fcdcf61bbd299f79aac4a63a47f27  matrix-k800_m800_n800.log
4c04b497c8f779f87dc9fc766d132165  matrix-k900_m900_n900.log
)

fmd5() {
	local file=$1
	if [[ -e $file ]]; then
		md5sum $file | awk '{print $1}'
	else
		echo "-ENOENT"
	fi
}

[[ -z ${MATRIX} ]] && MATRIX=matrix-fp32

MATRIX=$(echo ${MATRIX} | tr -d './')

for x in $(seq 100 100 1000)
do
	suffix=bin
	[[ ${TXT} ]] && suffix=log
	./${MATRIX} ${TXT:+-T} -O ${MATRIX}-k${x}_m${x}_n${x}.${suffix} -k $x -m $x -n $x
done


check_md5() {
	local md5_file=( ${@} )

	for ((i = 0; i < $(( ${#md5_file[@]} / 2 )); i++))
	do
		md5_correct=${md5_file[ $(( $i * 2 )) ]}
		file=${md5_file[ $(( $i * 2 + 1 )) ]}

		md5_real=$(fmd5 ${file})

		if [[ ${md5_correct} != ${md5_real} ]]; then
			printf "\033[31mFAILED\t%s\t%s != %s\033[m\n" $file $md5_correct $md5_real
		else
			printf "\033[32mSUCCESS\t%s\t%s\033[m\n" $file $md5_correct
		fi
	done
}

if [[ ${TXT} ]]; then
	check_md5 ${DATAS_MD5_FILE_TXT[@]}
else
	check_md5 ${DATAS_MD5_FILE_BIN[@]}
fi
