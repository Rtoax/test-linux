#!/bin/bash
# Usage: [TXT=1] ./matrix-md5.sh
set -e

DATAS_MD5_FILE_BIN=(
d89606d5e485fff33fb295c6b5f2d974  matrix-c-fp32-k1000_m1000_n1000.bin
db4121f6cb258573aacf608d75e89e12  matrix-c-fp32-k100_m100_n100.bin
c3312f95aff9dfdeb8bfde5bc692dea2  matrix-c-fp32-k200_m200_n200.bin
40f12a81ca614f7f6122595140e5e89a  matrix-c-fp32-k300_m300_n300.bin
0d0262b210dec31b68eb0e56f683d2c6  matrix-c-fp32-k400_m400_n400.bin
c42ca9f2f331960dc0bcfc13dc34cd43  matrix-c-fp32-k500_m500_n500.bin
737b6716210e973074fd9581b827b2a0  matrix-c-fp32-k600_m600_n600.bin
2f65c29fa103f83db1308d9d0c9faadf  matrix-c-fp32-k700_m700_n700.bin
28bbbaabef850ca0544a1d1150a8f682  matrix-c-fp32-k800_m800_n800.bin
f93cbdecf242f096b0190d5746a15933  matrix-c-fp32-k900_m900_n900.bin
d89606d5e485fff33fb295c6b5f2d974  matrix-c-fp64-k1000_m1000_n1000.bin
db4121f6cb258573aacf608d75e89e12  matrix-c-fp64-k100_m100_n100.bin
c3312f95aff9dfdeb8bfde5bc692dea2  matrix-c-fp64-k200_m200_n200.bin
40f12a81ca614f7f6122595140e5e89a  matrix-c-fp64-k300_m300_n300.bin
0d0262b210dec31b68eb0e56f683d2c6  matrix-c-fp64-k400_m400_n400.bin
c42ca9f2f331960dc0bcfc13dc34cd43  matrix-c-fp64-k500_m500_n500.bin
737b6716210e973074fd9581b827b2a0  matrix-c-fp64-k600_m600_n600.bin
2f65c29fa103f83db1308d9d0c9faadf  matrix-c-fp64-k700_m700_n700.bin
28bbbaabef850ca0544a1d1150a8f682  matrix-c-fp64-k800_m800_n800.bin
f93cbdecf242f096b0190d5746a15933  matrix-c-fp64-k900_m900_n900.bin
21c4bb8d9c96a4b9b60b0bb0f1685a89  matrix-fp16-k1000_m1000_n1000.bin
da9e07cec8a85f819d696832ba558c12  matrix-fp16-k100_m100_n100.bin
2df85860b6fc17a3899f36848b0f9989  matrix-fp16-k200_m200_n200.bin
9811ea550a6782f5d0adf1767fd14853  matrix-fp16-k300_m300_n300.bin
013fe9a1c08ea42c3bf0b5f2ed14db24  matrix-fp16-k400_m400_n400.bin
c4cd3b7cfd23384138835d9fb93b22e4  matrix-fp16-k500_m500_n500.bin
f6d3f89443d8fc6097252286bbc16b68  matrix-fp16-k600_m600_n600.bin
bc268a1d9f7e137b4511cbb7b758afeb  matrix-fp16-k700_m700_n700.bin
a09e8101a98f27216e16a5ca8912827f  matrix-fp16-k800_m800_n800.bin
c2b827d63317f62c63c045a892f0d725  matrix-fp16-k900_m900_n900.bin
629bbfbc540ecf9b8614c3bade229f0c  matrix-fp32-k1000_m1000_n1000.bin
7e5ade454b857d4d9be5e53b6c7a1225  matrix-fp32-k100_m100_n100.bin
c233b4cc0022c678d5cb6a9ea0c456d6  matrix-fp32-k200_m200_n200.bin
2882c5f1ff6c747b0a35e85b95c4057d  matrix-fp32-k300_m300_n300.bin
18a77e80a97373af5478090d0369d9c5  matrix-fp32-k400_m400_n400.bin
1ee287d585d229c9c17f84c7011d55a5  matrix-fp32-k500_m500_n500.bin
93f206bd99fb13075dee77cd98485202  matrix-fp32-k600_m600_n600.bin
c64e35c886346e397885c4c17a7174fc  matrix-fp32-k700_m700_n700.bin
109596205a435e9dafa91d29b905962f  matrix-fp32-k800_m800_n800.bin
da851493a22d75385b8e50ead6869e2d  matrix-fp32-k900_m900_n900.bin
e0c96ef9996d0bcf6cc6e91de49627b5  matrix-fp64-k1000_m1000_n1000.bin
cfc0f082661decee02018d2210e489ce  matrix-fp64-k100_m100_n100.bin
791ce35e362db48782d0d4c618490fef  matrix-fp64-k200_m200_n200.bin
839f8971319ca8e1e3e3d8a5ea72b30d  matrix-fp64-k300_m300_n300.bin
a47ca536e754dd7e295147d262915842  matrix-fp64-k400_m400_n400.bin
3fb1e74f5bbe3789799e3723e1a52180  matrix-fp64-k500_m500_n500.bin
07ecb81cda78317adc86413aa1aa9a9f  matrix-fp64-k600_m600_n600.bin
d09ad7ec009db0ec0b9b0d38164c98a8  matrix-fp64-k700_m700_n700.bin
e31490a66def49afea69ee91280b87c0  matrix-fp64-k800_m800_n800.bin
97df85664ec4becfbeda5d45f4ca835c  matrix-fp64-k900_m900_n900.bin
1c2db47428902fa45d2c7df7242becdb  matrix-int8-k1000_m1000_n1000.bin
8847f4ddbbb86988c057b4404d173097  matrix-int8-k100_m100_n100.bin
481eeb64dc11085fb37d22198cb4b466  matrix-int8-k200_m200_n200.bin
b387ca3cb5990f93708d106c4dde9dd1  matrix-int8-k300_m300_n300.bin
25d295c55aaa2b2e8fee0298050207c1  matrix-int8-k400_m400_n400.bin
50b3b4d647304122dd878c56a531a4bf  matrix-int8-k500_m500_n500.bin
d8726603b3ce6a8137db3b83a274efd9  matrix-int8-k600_m600_n600.bin
edb25ae7aacaee696b5fd0fa1e25afaf  matrix-int8-k700_m700_n700.bin
6a01281261be665136a2474c8ecbd992  matrix-int8-k800_m800_n800.bin
56c27869d60cd3014f0b3bc98d89bf41  matrix-int8-k900_m900_n900.bin
)

DATAS_MD5_FILE_TXT=(
0cf9b2292c4a24d41b9ccaea5a29571f  matrix-c-fp32-k1000_m1000_n1000.log
d04dcf17d1135ccb6458fb1efd605159  matrix-c-fp32-k100_m100_n100.log
bbb8a1074f68b5c9735ae6c77ec0bdf4  matrix-c-fp32-k200_m200_n200.log
05de7226992bda26ba86317efb1a8e47  matrix-c-fp32-k300_m300_n300.log
7937cda9d14d7bc584ce0f7c0aa47850  matrix-c-fp32-k400_m400_n400.log
9bde03b383a4fefae62821af2515c783  matrix-c-fp32-k500_m500_n500.log
9abc774828ddb102b748dd11f6ee7707  matrix-c-fp32-k600_m600_n600.log
ad5a9e526b90639a7794f75e4e1b8f65  matrix-c-fp32-k700_m700_n700.log
f5902134613d73f204cf7b5f1f858beb  matrix-c-fp32-k800_m800_n800.log
4e6be1c7a41e3cab390e518eb764fbbe  matrix-c-fp32-k900_m900_n900.log
0cf9b2292c4a24d41b9ccaea5a29571f  matrix-c-fp64-k1000_m1000_n1000.log
d04dcf17d1135ccb6458fb1efd605159  matrix-c-fp64-k100_m100_n100.log
bbb8a1074f68b5c9735ae6c77ec0bdf4  matrix-c-fp64-k200_m200_n200.log
05de7226992bda26ba86317efb1a8e47  matrix-c-fp64-k300_m300_n300.log
7937cda9d14d7bc584ce0f7c0aa47850  matrix-c-fp64-k400_m400_n400.log
9bde03b383a4fefae62821af2515c783  matrix-c-fp64-k500_m500_n500.log
9abc774828ddb102b748dd11f6ee7707  matrix-c-fp64-k600_m600_n600.log
ad5a9e526b90639a7794f75e4e1b8f65  matrix-c-fp64-k700_m700_n700.log
f5902134613d73f204cf7b5f1f858beb  matrix-c-fp64-k800_m800_n800.log
4e6be1c7a41e3cab390e518eb764fbbe  matrix-c-fp64-k900_m900_n900.log
cbe4744fee1046f1ac8c37afa9231527  matrix-fp16-k1000_m1000_n1000.log
0648740b5922912068076a86ae8fc3a1  matrix-fp16-k100_m100_n100.log
bcc7ce3120e12481993c9ccea379a1b1  matrix-fp16-k200_m200_n200.log
3b0d7de0869c67d9f48bf95979cce612  matrix-fp16-k300_m300_n300.log
ca36dd3c13af2df0374243cc5a82108f  matrix-fp16-k400_m400_n400.log
94aed63750ae5e41bc2f0cf93add905f  matrix-fp16-k500_m500_n500.log
6be3b0aad66fccbcfe5d00165e717b96  matrix-fp16-k600_m600_n600.log
d649735dda7ffa1a4589440b83cae1e1  matrix-fp16-k700_m700_n700.log
712d79c82a08cb57a5edbc9ba266830c  matrix-fp16-k800_m800_n800.log
018b571c220cb4d5a77ed21956a6a861  matrix-fp16-k900_m900_n900.log
cf17414f95852dbe1b2478633d5edc6a  matrix-fp32-k1000_m1000_n1000.log
05c6a3006b74f07df9e94d5145e37891  matrix-fp32-k100_m100_n100.log
abf5abb1fb2363ce998aafd112d4adc2  matrix-fp32-k200_m200_n200.log
d375ad416950f24302792003560df260  matrix-fp32-k300_m300_n300.log
67cb3132b590074d034be0b072910c7b  matrix-fp32-k400_m400_n400.log
1cca9b04dd8b72dbec4a6e04b4a764a2  matrix-fp32-k500_m500_n500.log
a2ead9faf905c7e779f2de5e4c0a9851  matrix-fp32-k600_m600_n600.log
1e56b5a58830ac120787e49d61b359d3  matrix-fp32-k700_m700_n700.log
8b2fcdcf61bbd299f79aac4a63a47f27  matrix-fp32-k800_m800_n800.log
4c04b497c8f779f87dc9fc766d132165  matrix-fp32-k900_m900_n900.log
81994c5a16bc1bfe8a694fb52d18ea3d  matrix-fp64-k1000_m1000_n1000.log
e4d6810789d0434eb5099f19648f538c  matrix-fp64-k100_m100_n100.log
fd82f06aaa660ce8eb5beafe79384319  matrix-fp64-k200_m200_n200.log
edbea07a71d7994ddeb234b193680c0c  matrix-fp64-k300_m300_n300.log
59120547b74fa76212969ccd9311dff4  matrix-fp64-k400_m400_n400.log
be0a5e0fa1dfe84f4b7ba25a5b60cc0c  matrix-fp64-k500_m500_n500.log
9a1289dfb41fe7eebe312b18fe4e8167  matrix-fp64-k600_m600_n600.log
54892052ac441aca89046a0432af0b82  matrix-fp64-k700_m700_n700.log
81fb317b23c89a460a817b67adb0052c  matrix-fp64-k800_m800_n800.log
a8f93bff2fa9b131001bb57dff8adf9d  matrix-fp64-k900_m900_n900.log
7c7a3318c5de7dff8804d45c5b21865f  matrix-int8-k1000_m1000_n1000.log
05f636126290df68124cc62f2f785387  matrix-int8-k100_m100_n100.log
c2062ad7f83e546c753c9ed41ed754b0  matrix-int8-k200_m200_n200.log
83e726abab803b140f7eb6034c6de030  matrix-int8-k300_m300_n300.log
303ceefc2641921aa38b9cc93038ea5f  matrix-int8-k400_m400_n400.log
0c3ef39a5b4378b904a06c7b9401107e  matrix-int8-k500_m500_n500.log
efcfa08b576df28f35e7dcee94ea8492  matrix-int8-k600_m600_n600.log
ae7b7f6242239974b623a9b03a37fee9  matrix-int8-k700_m700_n700.log
2af4692450a6a5668822aec85280c5c7  matrix-int8-k800_m800_n800.log
bff3d310a3cda0e3169704da6e838dc4  matrix-int8-k900_m900_n900.log
)

fmd5() {
	local file=$1
	if [[ -e $file ]]; then
		md5sum $file | awk '{print $1}'
	else
		echo "-ENOENT"
	fi
}

for prog in matrix-fp16 matrix-fp32 matrix-fp64 matrix-int8 matrix-c-fp32 matrix-c-fp64
do
	prog=$(echo ${prog} | tr -d './')

	for x in $(seq 100 100 1000)
	do
		suffix=bin
		[[ ${TXT} ]] && suffix=log
		./${prog} ${TXT:+-T} -O ${prog}-k${x}_m${x}_n${x}.${suffix} -k $x -m $x -n $x
	done
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
