#!/bin/bash

prog_name=clang-sort

cflags=""

clang_orig()
{
	clang ${cflags} sort.c -o ${prog_name}.out
}

clang_gen_prof()
{
	local _prog=${prog_name}-genprof.out

	clang ${cflags} sort.c -o ${_prog} \
		-fexperimental-new-pass-manager \
		-fprofile-generate

	# Generate default.profraw
	./${_prog}

	[[ ! -z default.profraw ]] && mv default*.profraw default.profraw
}

clang_fdo()
{
	local _prog_pgo=${prog_name}-pgo.out
	local _prog_fdo=${prog_name}-fdo.out


	clang_gen_prof

	llvm-profdata merge --output default.profdata default.profraw

	clang ${cflags} sort.c -o ${_prog_pgo} \
		-fexperimental-new-pass-manager \
		-fprofile-use=default.profdata

	# FIXME: How to FDO?
	ln -s ${_prog_pgo} ${_prog_fdo}
}


. clean.sh

clang_orig
clang_fdo

