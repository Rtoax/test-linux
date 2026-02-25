#!/bin/bash
# This is dialog library for anaconda-pre-dialog and other commands
#

DIALOG_LIBS_ROOT=$(dirname `realpath $0`)

display_result()
{
	dialog \
		--backtitle "${backtitle}" \
		--title "$1" \
		--no-collapse \
		--msgbox "$result" 0 0
}

# $1 - input string
# print 1 if no space
# print >1 if has space
has_space()
{
	echo "x${1}x" | awk '{print NF}'
}

# $1 - ip address
# return 1-failed, 0-success
# echo FAIL-failed, OK-success
check_ipv4_address()
{
	local addr=$1
	local -a arr


	# '0.0.0.0.' is ill, only three '.' needed here.
	local nr_dot=$(echo $addr | tr -cd "." | wc -c)
	if [[ $nr_dot > 3 ]]; then
		echo "FAIL"
		return 1
	fi

	arr+=( $(echo $addr | awk -F '.' '{print $1}') )
	arr+=( $(echo $addr | awk -F '.' '{print $2}') )
	arr+=( $(echo $addr | awk -F '.' '{print $3}') )
	arr+=( $(echo $addr | awk -F '.' '{print $4}') )
	arr+=( $(echo $addr | awk -F '.' '{print $5}') )


	# 0.0.0.0.0 is not OK
	#         ^
	[[ ! -z ${arr[4]} ]] && echo "FAIL" && return 1

	for ((i = 0; i < 4; i++))
	do
		local a=${arr[$i]}
		# Empty
		if [[ -z $a ]]; then
			echo "FAIL"
			return 1
		# Number
		elif [[ -z "$(echo $a | grep -E '^[[:digit:]]*$')" ]]; then
			echo "FAIL"
			return 1
		# 0-255
		elif (( $a < 0 )) || (( $a > 255 )); then
			echo "FAIL"
			return 1
		fi
	done

	echo "OK"
	return 0
}

# -k,--kickstart	brand new kickstart to create
# -n,--name			repo name
# -u,--baseurl		repo baseurl
kickstart_repo()
{
	TEMP=$(getopt \
		--options n:u:k: \
		--long name: \
		--long baseurl: \
		--long kickstart: \
		-n kickstart_repo -- "$@")

	local name baseurl kickstart

	test $? != 0 && (
		result="Wrong exec getopt"
		display_result "Packages fatal"
		result=
	)

	eval set -- "$TEMP"

	while true; do
		case $1 in
		-n | --name)
			shift
			name=$1
			shift
			;;
		-u | --baseurl)
			shift
			baseurl=$1
			shift
			;;
		-k | --kickstart)
			shift
			kickstart=$1
			shift
			;;
		--)
			shift
			break
			;;
		esac
	done

	if [[ -z $kickstart ]]; then
		result="Must specify kickstart file."
		display_result "Packages fatal"
		result=
		return 0
	fi

	cat >>$kickstart <<-END
repo --name="${name}" --baseurl="${baseurl}"
END
}

# -k,--kickstart         brand new kickstart to create
# --hostname             set hostname
# --bootproto-dhcp       DHCP
# --bootproto-static     STATIC
kickstart_network()
{
	TEMP=$(getopt \
		--options k: \
		--long kickstart: \
		--long hostname: \
		--long bootproto-dhcp \
		--long bootproto-static \
		-n kickstart_repo -- "$@")

	test $? != 0 && (
		result="Wrong exec getopt"
		display_result "Network fatal"
		result=
	)

	eval set -- "$TEMP"

	local PROTO_DHCP=DHCP
	local PROTO_STATIC=STATIC

	local bootproto hostname kickstart


	while true; do
		case $1 in
		-k | --kickstart)
			shift
			kickstart=$1
			shift
			;;
		--hostname)
			shift
			hostname=$1
			shift
			;;
		--bootproto-dhcp)
			shift
			bootproto=$PROTO_DHCP
			;;
		--bootproto-static)
			shift
			bootproto=$PROTO_STATIC
			;;
		--)
			shift
			break
			;;
		esac
	done

	if [[ -z $kickstart ]]; then
		result="Must specify kickstart file."
		display_result "Network fatal"
		result=
		return 0
	fi

	[[ -z $hostname ]] && hostname=localhost

	# Create brand new kickstart
	cat >$kickstart <<-END
# ${KS_HDR_MAGIC}
# Network Config Kickstart
network --hostname=${hostname}
END

	# Different case of network config
	case $bootproto in
	$PROTO_DHCP)
		cat >>$kickstart <<-END
network --bootproto=dhcp
END
		;;
	$PROTO_STATIC)
		cat >>$kickstart <<-END
network --bootproto=static
END
		;;
	esac
}

# -k,--kickstart	brand new kickstart to create
kickstart_packages()
{
	TEMP=$(getopt \
		--options k: \
		--long kickstart: \
		-n kickstart_packages -- "$@")

	local kickstart

	test $? != 0 && (
		result="Wrong exec getopt"
		display_result "Packages fatal"
		result=
	)

	eval set -- "$TEMP"

	while true; do
		case $1 in
		-k | --kickstart)
			shift
			kickstart=$1
			shift
			;;
		--)
			shift
			break
			;;
		esac
	done

	if [[ -z $kickstart ]]; then
		result="Must specify kickstart file."
		display_result "Packages fatal"
		result=
		return 0
	fi

	cat >$kickstart <<-END
# ${KS_HDR_MAGIC}
# We don't know about this product, and in order to be able to install it
# successfully, we give it a default automatic packages installation.
# created by ostools.

%packages
@^minimal-environment
%end
END
}

# -k,--kickstart	specify kickstart to modify
# -g,--group	group name, default wheel
# -n,--name		user name
# -p,--password	user password
kickstart_user()
{
	TEMP=$(getopt \
		--options k:g:n:p: \
		--long kickstart: \
		--long group: \
		--long name: \
		--long password: \
		-n kickstart_user -- "$@")

	local kickstart group name password gecos

	test $? != 0 && (
		result="Wrong exec getopt"
		display_result "Create user fatal"
		result=
	)

	eval set -- "$TEMP"

	while true; do
		case $1 in
		-k | --kickstart)
			shift
			kickstart=$1
			shift
			;;
		-g | --group)
			shift
			group=$1
			shift
			;;
		-n | --name)
			shift
			name=$1
			shift
			;;
		-p | --password)
			shift
			password=$1
			shift
			;;
		--)
			shift
			break
			;;
		esac
	done

	if [[ -z $kickstart ]] || [[ ! -f $kickstart ]]; then
		result="Empty or non exist kickstart file: $kickstart."
		display_result "Create user fatal"
		result=
		return 0
	fi

	[[ -z $group ]] && group=wheel

	if [[ -z $name ]]; then
		result="Empty username."
		display_result "Create user fatal"
		result=
		return 0
	fi
	if [[ -z "${password}" ]]; then
		result="Empty password."
		display_result "Create user fatal"
		result=
		return 0
	fi

	local user_args=()
	local password_crypt="${password}"

	# Crypt password. We should use encrypted passwords instead of plaintext
	# passwords whenever possible. Like ostools commit 7d45de4e06ee("lorax-tmpl:
	# Add mkpasswd for install.img") add the encryption tool mkpasswd to
	# install.img.
	if [[ -e /usr/bin/openssl ]]; then
		password_crypt=$(openssl passwd -6 -salt rongtao "${password}")
		user_args+=("--iscrypted")
	elif [[ -e /usr/bin/mkpasswd ]]; then
		password_crypt=$(mkpasswd -s "${password}")
		user_args+=("--iscrypted")
	fi

	cat >>$kickstart <<-END
user --groups=$group --name=$name --password='${password_crypt}' ${user_args[@]} --gecos="$name"
END
}

# -k,--kickstart	specify kickstart to modify
# -d,--target-disk	specify target disk
kickstart_partition()
{
	TEMP=$(getopt \
		--options k:d: \
		--long kickstart: \
		--long target-disk: \
		-n kickstart_partition -- "$@")

	local kickstart target_disk

	test $? != 0 && (
		result="Wrong exec getopt"
		display_result "Partition fatal"
		result=
	)

	eval set -- "$TEMP"

	while true; do
		case $1 in
		-k | --kickstart)
			shift
			kickstart=$1
			shift
			;;
		-d | --target-disk)
			shift
			target_disk=$1
			shift
			;;
		--)
			shift
			break
			;;
		esac
	done

	if [[ -z $kickstart ]] || [[ ! -f $kickstart ]]; then
		result="Empty or non exist kickstart file: $kickstart."
		display_result "Partition fatal"
		result=
		return 0
	fi

	if [[ -z $target_disk ]] || [[ ! -f $kickstart ]]; then
		result="Must specify target disk with -d,--target-disk."
		display_result "Partition fatal"
		result=
		return 0
	fi

	cat >>$kickstart <<-END
# We don't know about this product, and in order to be able to install it
# successfully, we give it a default automatic partition.
# created by ostools.

clearpart --all --initlabel
ignoredisk --only-use=${target_disk}
autopart
END
}

# Example: vda(200G), vdb(100G), vdc(90G)
# If install OS into vdc, you have to change the boot order.
# (vda has high priority)
get_smallest_disk()
{
	local disks
	local sizes
	local minimal_size=999999999999999999
	local minimal_idx=0
	local tmpfile=$(mktemp)

	# -b: print bytes
	# TYPE=disk
	# vda, sda, hda, nvmexxx
	lsblk -b \
		| grep disk \
		| grep -e ^vd -e ^sd -e ^hd -e ^nvme \
		| awk '{print $1" "$4}' > ${tmpfile}

	while read line
	do
		local disk=$(echo $line | awk '{print $1}')
		local size=$(echo $line | awk '{print $2}')
		disks+=( $disk )
		sizes+=( $size )
	done < ${tmpfile}

	rm -f ${tmpfile}

	# For example: c is the minimal
	# disks=( a b c )
	# sizes=( 2 3 1 )
	for ((i = 0; i < ${#sizes[@]}; i++))
	do
		test ${sizes[$i]} -le $minimal_size && {
			minimal_size=${sizes[$i]}
			minimal_idx=$i
		}
	done

	echo "${disks[$minimal_idx]}"
}

# Get Product= from .buildstamp
buildstamp_product()
{
	local config_path=/.buildstamp

	# Use ENV first
	[[ ! -z ${BUILDSTAMP_PRODUCT} ]] && \
		echo ${BUILDSTAMP_PRODUCT} && \
		return 0

	[[ ! -f $config_path ]] && config_path=${DIALOG_LIBS_ROOT}/../../.buildstamp

	local product=$(grep "Product=" $config_path)
	# Product=ABC -> ABC
	echo ${product:8} | xargs
}

apply_modules()
{
	[[ -z ${DIALOG_MODULES_ROOT} ]] && return 0

	# For each modules
	for dir in $(echo ${DIALOG_MODULES_ROOT}/[0-9][0-9]* | sort)
	do
		local _moddir=$(realpath ${dir})

		[[ ! -f $_moddir/module-setup.sh ]] && continue

		unset depends install
		install() { true; }
		depends() { true; }

		. $_moddir/module-setup.sh

		# Call
		moddir=$_moddir depends
		moddir=$_moddir install

		unset depends install
	done
}

declare -a cmdline_array

parse_proc_cmdline()
{
	local _cmdline=$(cat /proc/cmdline)

	# Skip BOOT_IMAGE=
	_cmdline=${_cmdline:11}

	for c in ${_cmdline}
	do
		cmdline_array+=( "$c" )
	done
}
parse_proc_cmdline

get_cmdline()
{
	echo "${cmdline_array[@]}"
}

add_cmdline()
{
	[[ -z $1 ]] && return 0
	cmdline_array+=( "$1" )
}
