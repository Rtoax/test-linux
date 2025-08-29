#!/bin/bash
# Check the blas output matrix file MD5 Checksum

set -e

# NOTE: Assuming that the metax mars x203 is accurate data.
DATAS=(
475e326dc09eedd5059d448c79666660  AXPY_FP32-blas.bin
df2ab80fe7f309e2cfec8f472640c840  AXPY_FP64-blas.bin
0285142871bb875fbdace274db254bc2  COPY_FP32-blas.bin
72d9326fb88f255bb04bd2485b5757cc  COPY_FP64-blas.bin
0285142871bb875fbdace274db254bc2  DOT_FP32-blas.bin
72d9326fb88f255bb04bd2485b5757cc  DOT_FP64-blas.bin
a8748d5484ca2127ac1b3ca1949bdd38  GEMMEx_FP16-blas.bin
033980949cfb51c04711301df6f1e8b4  GEMMEx_FP32-blas.bin
c062a759dfb8921737514259eb2cae9d  GEMMEx_FP64-blas.bin
bca715c54871ae1b0de7da3e9123d9c4  GEMMEx_INT8-blas.bin
a8748d5484ca2127ac1b3ca1949bdd38  GEMM_FP16-blas.bin
033980949cfb51c04711301df6f1e8b4  GEMM_FP32-blas.bin
c062a759dfb8921737514259eb2cae9d  GEMM_FP64-blas.bin
a8748d5484ca2127ac1b3ca1949bdd38  MATMUL_FP16-blas.bin
e87358440c9b63b252480c5ef169130d  MATMUL_FP32-blas.bin
0556997c0288e879c7b81425985f8503  MATMUL_FP64-blas.bin
c8a5c3b49f0331749d0dbb71c5f76bad  MATMUL_INT8-blas.bin
db6b9a5d7322e5b6823660c0d3548726  NRM2_FP32-blas.bin
9e94ecf0511432d782bab2e01f7e84bf  NRM2_FP64-blas.bin
8a760fdab9b0f709b4dd8542fa10f0b1  SCAL_FP32-blas.bin
05c6ff6c53cac2c1e0b28af4946dc93d  SCAL_FP64-blas.bin
)

fmd5() {
	local file=$1
	if [[ -e $file ]]; then
		md5sum $file | awk '{print $1}'
	else
		echo "-ENOENT"
	fi
}

make blas
./blas -O blas.bin -k 1000 -m 1000 -n 1000

for ((i = 0; i < $(( ${#DATAS[@]} / 2 )); i++))
do
	md5_correct=${DATAS[ $(( $i * 2 )) ]}
	file=${DATAS[ $(( $i * 2 + 1 )) ]}

	md5_real=$(fmd5 ${file})

	if [[ ${md5_correct} != ${md5_real} ]]; then
		printf "\033[31mFAILED\t%s\t%s != %s\033[m\n" $file $md5_correct $md5_real
	else
		printf "\033[32mSUCCESS\t%s\t%s\033[m\n" $file $md5_correct
	fi
done
