#!/bin/bash

set -e

. config
. clean.sh

prog_name=clang-sort

profdata=${prog_name}.profdata

cflags="${CONFIG_CFLAGS}"
srcs="${CONFIG_SRC}"

clang_orig()
{
	clang ${cflags} ${srcs} -o ${prog_name}.out
}

clang_gen_prof()
{
	local _prog=${prog_name}-genprof.out

	clang ${cflags} ${srcs} -o ${_prog} \
		-fexperimental-new-pass-manager \
		-fprofile-generate

	# Generate default.profraw
	./${_prog}

	llvm-profdata merge --output ${profdata} default*.profraw
}

clang_fdo()
{
	local _prog_pgo=${prog_name}-pgo.out
	local _prog_fdo=${prog_name}-fdo.out


	clang_gen_prof

	clang ${cflags} ${srcs} -o ${_prog_pgo} \
		-fexperimental-new-pass-manager \
		-fprofile-use=${profdata}

	# FIXME: How to FDO?
	ln -s ${_prog_pgo} ${_prog_fdo}
}


clang_orig
clang_fdo

size ${prog_name}*.out
md5sum ${prog_name}*.out
