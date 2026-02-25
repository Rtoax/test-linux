#!/bin/bash
# Copyright (C) 2022-2026 Rong Tao
#
set -e

readonly ANACONDA_CMD_ROOT_DIRECTORY=$(dirname `realpath $0`)
readonly PRODUCT_ROOTDIR=$ANACONDA_CMD_ROOT_DIRECTORY/product.d/
readonly ISOCFG_ROOTDIR=$ANACONDA_CMD_ROOT_DIRECTORY/iso.cfg.d/


###############################################################################
# product.img

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

###############################################################################
# isocfgcpy

# Arguments
iso_rootdir=
iso_product=

# iso original LABEL=
iso_label_orig=
iso_arch=
sys_arch=$(uname -m)


__iso_config_copy_usage__()
{
	echo -e "
isocfgcpy

 -r, --rootdir [DIR]
                 specify ISO 9660 root directory
                 How to get ISO root directory:\033[2m
                 $ mkdir a
                 $ sudo mount a.iso a
                 $ sudo cp -a a dir   <<== dir is what you need
\033[m
 -p, --product [PRODUCT]
                 specify a product to copy, -l,--list get valide product list
 -l, --list      list all support product.

 -a, --arch [ARCH]
                 specify architecture. In general, it does not need to be
                 specified, and it is obtained automatically

 -h, --help      show help info
"
	exit ${1-0}
}

_iso_config_copy()
{
	# Check needed Arguments
	[[ -z ${iso_rootdir} ]] && \
		echo "Need -r,--rootdir argument" && exit 1
	[[ -z ${iso_product} ]] && \
		echo "Need -p,--product argument" && exit 1

	# Get original ISO LABEL from iso directory
	local _tmp_line=$(grep "LABEL=" ${iso_rootdir}/EFI/BOOT/grub.cfg)
	iso_label_orig=$(echo ${_tmp_line#*LABEL=} | awk '{print $1}')

	# Get ISO architecture
	#  1. try get arch from .discinfo
	local discinfo=${iso_rootdir}/.discinfo
	if [[ -z ${iso_arch} ]] && [[ -e ${discinfo} ]]; then
		if [[ ! -z $(grep x86_64 ${discinfo} || true) ]]; then
			iso_arch=x86_64
		elif [[ ! -z $(grep aarch64 ${discinfo} || true) ]]; then
			iso_arch=aarch64
		fi
	fi
	#  2. try get arch from origin LABEL
	if [[ -z ${iso_arch} ]]; then
		if [[ ! -z $(echo $iso_label_orig | grep x86_64 || true) ]]; then
			iso_arch=x86_64
		elif [[ ! -z $(echo $iso_label_orig | grep aarch64 || true) ]]; then
			iso_arch=aarch64
		fi
	fi
	#  Not found arch
	if [[ -z ${iso_arch} ]]; then
		echo "Could not found architecture information, use -a,--arch"
		exit 1
	fi
	#  platform architecture != ISO architecture
	if [[ ${iso_arch} != ${sys_arch} ]]; then
		echo "Conflict architecture, ISO($iso_arch) != platform($sys_arch)"
		exit 1
	fi


	local src_dir=${ISOCFG_ROOTDIR}/${iso_product}/${iso_arch}
	local dst_dir=$(realpath ${iso_rootdir})

	# Print some information
	echo "==="
	echo "=== ISO LABEL=${iso_label_orig}"
	echo "=== SRC: ${src_dir}"
	echo "=== DST: ${dst_dir}"
	echo "==="

	# Copy all files to target iso directory
	cp -a ${src_dir}/* ${dst_dir}

	# Modify iso LABEL=
	sed -i "s|I_AM_LABEL|${iso_label_orig}|g" ${dst_dir}/EFI/BOOT/grub.cfg

	[[ ${iso_arch} == x86_64 ]] && \
		sed -i "s|I_AM_LABEL|${iso_label_orig}|g" ${dst_dir}/isolinux/isolinux.cfg

	echo "=== You can genisoimage right now!!!"
}

# $1 - detail, etc.
list_iso_product()
{
	local detail

	if [[ "$1" == "detail" ]]; then
		detail=YES
	fi

	for d in $(ls ${ISOCFG_ROOTDIR})
	do
		echo "${d} "
		[[ ! -z ${detail} ]] && [[ -e $ISOCFG_ROOTDIR/${d}/.readme ]] && \
			cat $ISOCFG_ROOTDIR/${d}/.readme | \
				head -n 2 | \
				sed 's/^/\t/g'
	done
}

__iso_config_copy__()
{
	TEMP=$(getopt \
		--options hr:p:la: \
		--long help \
		--long rootdir: \
		--long product: \
		--long list \
		--long arch: \
		-n $0 -- "$@")

	test $? != 0 && __iso_config_copy_usage__ 1

	eval set -- "$TEMP"

	while true; do
		case $1 in
		-h | --help)
			shift
			__iso_config_copy_usage__
			;;
		-r | --rootdir)
			shift
			iso_rootdir=$1
			[[ ! -d $iso_rootdir ]] && \
				echo "$iso_rootdir is not exist." && exit 1
			[[ ! -f ${iso_rootdir}/images/install.img ]] && \
				echo "$iso_rootdir is not iso directory." && exit 1
			if [[ ! -f ${iso_rootdir}/EFI/BOOT/grub.cfg ]] && \
				[[ ! -f ${iso_rootdir}/isolinux/isolinux.cfg ]]
			then
				echo "No found boot config in ${iso_rootdir}"
				exit 1
			fi
			shift
			;;
		-p | --product)
			shift
			iso_product=$1
			[[ ! -d $ISOCFG_ROOTDIR/${iso_product} ]] && \
				echo "Non exist product ${iso_product}, see -l,--list" && \
				exit 1
			shift
			;;
		-l | --list)
			shift
			echo
			echo "Product list:"
			echo
			list_iso_product detail | sed 's/^/ /g'
			echo
			exit 0
			;;
		-a | --arch)
			shift
			iso_arch=$1
			shift
			;;
		--)
			shift
			break
			;;
		esac
	done

	_iso_config_copy
}

###############################################################################
__usage__()
{
	echo "
anaconda

Subcommand:

 product.img     make a product.img for [Anaconda Customization Guide]
 isocfgcpy       copy isolinux.cfg/grub.cfg and other config into iso

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
	isocfgcpy)
		shift
		__iso_config_copy__ "$@"
		;;
	*)
		__usage__ 1
		;;
	esac
}

__main__ "$@"
