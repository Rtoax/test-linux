#!/bin/bash
# Check the blas MD5 Checksum
set -e

DATAS=(
	b3a041b5d93a5d4f800224374bc5f730  AXPY_FP32-blas.bin
	c4f2c1f9dc235525f5099fb876e105fa  AXPY_FP64-blas.bin
	a48d09206bd05d07357bbfc988971c52  COPY_FP32-blas.bin
	b83a11a4cf7cfad3f62917909dacb8f3  COPY_FP64-blas.bin
	a48d09206bd05d07357bbfc988971c52  DOT_FP32-blas.bin
	b83a11a4cf7cfad3f62917909dacb8f3  DOT_FP64-blas.bin
	3454aa4edb6f4f1c143c6ec3d5a77433  GEMMEx_FP16-blas.bin
	f11f16c38d41371ca79a1ede55498057  GEMMEx_FP32-blas.bin
	fce8dc64e569ee9488ad530b0695ede7  GEMMEx_FP64-blas.bin
	e175e5e7d7d6f0f1231a622f3ebf49f2  GEMMEx_INT8-blas.bin
	3454aa4edb6f4f1c143c6ec3d5a77433  GEMM_FP16-blas.bin
	f11f16c38d41371ca79a1ede55498057  GEMM_FP32-blas.bin
	fce8dc64e569ee9488ad530b0695ede7  GEMM_FP64-blas.bin
	3454aa4edb6f4f1c143c6ec3d5a77433  MATMUL_FP16-blas.bin
	f11f16c38d41371ca79a1ede55498057  MATMUL_FP32-blas.bin
	fce8dc64e569ee9488ad530b0695ede7  MATMUL_FP64-blas.bin
	e175e5e7d7d6f0f1231a622f3ebf49f2  MATMUL_INT8-blas.bin
	24be8e4fd41e6b8c3fbede463cb59259  NRM2_FP32-blas.bin
	99280b373bf88ca64a9a79d059123015  NRM2_FP64-blas.bin
	af5fd9e55ca9c2b98f6437728237ebdd  SCAL_FP32-blas.bin
	5d522bc2ecc01becb98e1b43179f67ea  SCAL_FP64-blas.bin
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
./blas -O blas.bin

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
