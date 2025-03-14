#!/bin/bash

Q() {
for m in $(find -name Makefile)
do
	line=$(sed -n '/SHELL =/=' $m)
	echo === $m, line $line
	sed "${line} a ifeq (\$(V),1)\n  Q =\nelse\n  Q = @\n  MAKEFLAGS += --no-print-directory\nendif\nexport Q\n" -i $m
done
}

Q2_NO_SHELL() {
for m in $(find -name Makefile)
do
	line=$(sed -n '/SHELL =/=' $m)
	[[ -z ${line} ]] && echo === $m no SHELL
done
}

CC() {
for m in $(find -name Makefile)
do
	echo === $m
	sed -i 's/@$(CC)/${Q}$(CC)/g' $m
	sed -i 's/@${CC}/${Q}$(CC)/g' $m
	sed -i 's/@$(CXX)/${Q}$(CXX)/g' $m
	sed -i 's/@${CXX}/${Q}$(CXX)/g' $m
	sed -i 's/@$(CLANG)/${Q}$(CLANG)/g' $m
	sed -i 's/@${CLANG}/${Q}$(CLANG)/g' $m
	sed -i 's/@rm/${Q}rm/g' $m
	sed -i 's/@${RM}/${Q}${RM}/g' $m
	sed -i 's/@make/${Q}make/g' $m
done
}

Q3() {
for m in $(find -name 'Makefile*')
do
	echo === $m
	start=$(sed -n '/ifeq ($(V),1)/=' $m)

	dir_level=$(echo $m | grep -o '/' | wc -l)
	dir_level=$(( ${dir_level} - 1 ))

	tlbuild_path=
	for ((i = 0; i < ${dir_level}; i++))
	do
		tlbuild_path=${tlbuild_path}../
	done
	tlbuild_path=${tlbuild_path}tlbuild.mk

	sed -i "${start},$(($start + 5))d" $m
	sed -i "s|export Q|include ${tlbuild_path}|g" $m
done
}

SHELL_1() {
for m in $(find -name 'Makefile*')
do
	has_tlbuild=$(grep 'include.*tlbuild.mk' $m 2>&1 >/dev/null && echo YES)

	dir_level=$(echo $m | grep -o '/' | wc -l)
	dir_level=$(( ${dir_level} - 1 ))

	tlbuild_path=
	if [[ -z ${has_tlbuild} ]]; then
		for ((i = 0; i < ${dir_level}; i++))
		do
			tlbuild_path=${tlbuild_path}../
		done
		tlbuild_path=${tlbuild_path}tlbuild.mk
	fi

	echo === $m === has_tlbuild=${has_tlbuild}, tlbuild_path=${tlbuild_path}

	if [[ ${has_tlbuild} ]]; then
		sed -i "/SHELL /d" $m
	else
		line=$(sed -n '/SHELL /=' $m)
		[[ -z ${line} ]] && continue

		echo "$m: line=${line}"
		sed -i "${line}s|.*|include ${tlbuild_path}|g" $m
	fi
done
}

SUBDIR() {
	for m in $(find -name 'Makefile')
	do
		tmp=$(mktemp -u tmp-XXXXXX)

		dir_level=$(echo $m | grep -o '/' | wc -l)
		dir_level=$(( ${dir_level} - 1 ))

		echo "========== $m ${dir_level}"
		build_nl=$(sed -n '/^sub-dir-build/=' ${m})
		if [[ -z ${build_nl} ]]; then
			continue
		fi
		subdir_path=
		for ((i = 0; i < ${dir_level}; i++))
		do
			subdir_path=${subdir_path}../
		done
		subdir_path=${subdir_path}template/

		sed -i "${build_nl}d" ${m}

		clean_nl=$(sed -n '/^sub-dir-clean/=' ${m})
		awk -v N=${clean_nl} -v line="include ${subdir_path}subdir-header.mk" \
			'NR==N{$0=line};1' ${m} > ${tmp}
		mv ${tmp} ${m}

		build_nl_target=$(sed -n '/^$(sub-dir-build):/=' ${m})
		sed -i "${build_nl_target}d" ${m}
		if [[ "$(awk -v N=${build_nl_target} 'NR==N' ${m} | grep -wo echo)" ]]; then
			sed -i "${build_nl_target}d" ${m}
		fi
		if [[ "$(awk -v N=${build_nl_target} 'NR==N' ${m} | grep -wo make)" ]]; then
			sed -i "${build_nl_target}d" ${m}
		fi
		clean_nl_target=$(sed -n '/^$(sub-dir-clean):/=' ${m})
		sed -i "${clean_nl_target}d" ${m}
		if [[ "$(awk -v N=${build_nl_target} 'NR==N' ${m} | grep -wo echo)" ]]; then
			sed -i "${clean_nl_target}d" ${m}
		fi
		awk -v N=${clean_nl_target} \
			-v line="include ${subdir_path}subdir-footer.mk" \
			'NR==N{$0=line};1' ${m} > ${tmp}
		mv ${tmp} ${m}

		test_nl_target=$(sed -n '/^test:/=' ${m})
		if [[ ${test_nl_target} ]]; then
			orig_line="$(awk -v N=${test_nl_target} 'NR==N' ${m})"
			awk -v N=${test_nl_target} \
				-v line="${orig_line} \$(sub-dir-test)" \
				'NR==N{$0=line};1' ${m} > ${tmp}
			mv ${tmp} ${m}
		fi
	done
}
SUBDIR
