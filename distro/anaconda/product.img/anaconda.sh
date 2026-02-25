#!/bin/bash
# Copyright (C) 2022-2026 Rong Tao
#
set -e

readonly ANACONDA_CMD_ROOT_DIRECTORY=$(dirname `realpath $0`)
readonly PRODUCT_ROOTDIR=$ANACONDA_CMD_ROOT_DIRECTORY/product.d/

product_dirs=()
product_odir=${PWD}

keep=


# $1 detail
list_all_product_dir()
{
	local detail

	if [[ "$1" == "detail" ]]; then
		detail=YES
	fi

	for d in $(ls ${PRODUCT_ROOTDIR})
	do
		echo "${d} "
		[[ ! -z ${detail} ]] && [[ -e $PRODUCT_ROOTDIR/${d}/.readme ]] && \
			cat $PRODUCT_ROOTDIR/${d}/.readme | \
				head -n 2 | \
				sed 's/^/\t/g'
	done
}

# $1 - a string or a directory
add_product_dir()
{
	local dir=$1
	local internal_dir=$PRODUCT_ROOTDIR/$dir

	# Use ostools's first
	if [[ -d ${internal_dir} ]]; then
		# conflicts directory warning
		if [[ -d ${internal_dir} ]] && [[ -d $dir ]]; then
			echo "=== WARN: conflicts ${internal_dir}(ostools) with ${dir}(custom)"
			echo "=== use ${internal_dir} first"
		fi

		[[ ! -f ${internal_dir}/.buildstamp ]] && echo "No .buildstamp found" && exit 1
		echo "=== Found ${internal_dir}"
		product_dirs+=( "${internal_dir}" )
	# Current directory
	elif [[ -d $dir ]]; then
		[[ ! -f $dir/.buildstamp ]] && echo "No .buildstamp found" && exit 1
		product_dirs+=( "$dir" )
	# Not found
	else
		echo "Unknown $dir, see -h, --help"
		exit 1
	fi

	# Add .depends for dependences
	if [[ -e ${internal_dir}/.depends ]]; then
		echo "=== Deps: $(cat ${internal_dir}/.depends)"
		for dep in $(cat ${internal_dir}/.depends)
		do
			add_product_dir ${dep}
		done
	fi

	return 0
}

# $1 - output directory
set_product_odir()
{
	local odir=$1

	[[ ! -d ${odir} ]] && echo "Non exist directory ${odir}" && exit 1

	product_odir=${odir}
}

__product_img_usage__()
{
	echo "
product.img

 -p, --product [PRODUCT-NAME]
                 specify a product to generate, if specify a directory, check
                 it's exist or not. if it's simple 'string', found the directory
                 under $PRODUCT_ROOTDIR, see -l,--list argument.
                 (may be listed multiple times, overwrite if exist, the first
                 input has the highest priority)
                 support: $(list_all_product_dir | tr -d '\n')

 -o, --output [DIR]
                 specify output directory, default: ${product_odir}

 -k, --keep      don't delete the temporary files which generated during create.

 -l, --list      list all support product.

 -h, --help      show help info
"
	exit ${1-0}
}

_product_img()
{
	[[ -z ${product_dirs[@]} ]] && echo "Need -p, --product" && exit 1

	local cur_dir=$PWD
	local tmpdir=$(mktemp -d product.img.XXXXXX)

	# Test temporary files may be generated during testing, and we
	# should clean them up.
	pushd ${PRODUCT_ROOTDIR}
	git clean -dfx || true
	popd

	# When we enter multiple product(-p), the .buildstamp of the last
	# input product will overwrite all the previous ones, so, using
	# the reverse order of the product_dirs array, the .buildstamp
	# description file of the first input product(-p) is used.
	for idx in $(seq $[${#product_dirs[@]} - 1] -1 0 )
	do
		local p=${product_dirs[$idx]}
		cp -a ${p}/* ${p}/.buildstamp ${tmpdir}
	done

	pushd ${tmpdir}
	# Remove useless files/directories
	rm -f README.md README.txt README
	# Archive
	find . | cpio -c -o --quiet | gzip -9cv > ${product_odir}/product.img
	popd

	[[ -z ${keep} ]] && rm -rf ${tmpdir}

	echo "Done to generate ${product_odir}/product.img!!!"
}


__product_img__()
{
	TEMP=$(getopt \
		--options hp:lo:k \
		--long help \
		--long product: \
		--long output: \
		--long keep \
		--long list \
		-n $0 -- "$@")

	test $? != 0 && __product_img_usage__ 1

	eval set -- "$TEMP"

	while true; do
		case $1 in
		-h | --help)
			shift
			__product_img_usage__
			;;
		-p | --product)
			shift
			add_product_dir $1
			shift
			;;
		-l | --list)
			shift
			echo
			echo "Product template list:"
			echo
			list_all_product_dir detail | sed 's/^/ /g'
			echo
			exit 0
			;;
		-o | --output)
			shift
			set_product_odir $1
			shift
			;;
		-k | --keep)
			shift
			keep=YES
			;;
		--)
			shift
			break
			;;
		esac
	done

	_product_img
}

__usage__()
{
	echo "
anaconda

Subcommand:

 product.img     make a product.img for [Anaconda Customization Guide]

Option args:

 -v, --verbose   show detail dur running
 -h, --help      show help info

Example:

 anaconda -v product.img -h
"
	exit ${1-0}
}

__main__()
{
	case $1 in
	-v | --verbose)
		shift
		set -x
		;;
	-h | --help)
		shift
		__usage__
		;;
	esac

	case $1 in
	product.img)
		shift
		__product_img__ "$@"
		;;
	*)
		__usage__ 1
		;;
	esac
}

__main__ "$@"
