#!/bin/bash

################################################################################
#
#   UNIX域Socket抓包
#
#   作者：荣涛
#   时间：2020年11月9日
#
################################################################################

exe_name=$0
eth_port="lo"

#UNIX socket 文件路径
unix_path=/tmp/unix.sock
unix_path_original="$unix_path.original"
ARG_UNIX_PATH="-u"
ARG_UNIX_PATH_S="UNIX socket path name."

#抓包文件
pcap_switch=0
pcap_file=pcap.pcap
ARG_PCAP_FILE="-f"
ARG_PCAP_FILE_S="Pcap File Name. default $pcap_file, no set no save."

#临时端口
tcp_port=8087
ARG_TCP_PORT="-p"
ARG_TCP_PORT_S="TMP port for swap UNIX socket. default $tcp_port"

#显示包的比特信息，如下：
# 0x0000:  4500 0034 52ae 4000 4006 ea13 7f00 0001
# 0x0010:  7f00 0001 c82a 07cf 6a88 73d9 bfa9 666c
# 0x0020:  8010 01f8 fe28 0000 0101 080a a2d6 9545
# 0x0030:  a2d6 9545
pbits_flag=0
ARG_PBITS_DETAIL="-x"
ARG_PBITS_DETAIL_S="Show Packet Bits."

#帮助信息
ARG_USAGE="-h"
ARG_USAGE_S="Show usage."

#tcpdump的参数
ARG_TCPDUMP=" -i $eth_port -netvvv -N -q "

function usage()
{
	printf "\n"
	printf "$exe_name [option] [value]\n"
	printf "\n"
	printf "    $ARG_UNIX_PATH   $ARG_UNIX_PATH_S \n"
	printf "    $ARG_PCAP_FILE   $ARG_PCAP_FILE_S\n"
	printf "    $ARG_TCP_PORT   $ARG_TCP_PORT_S\n"
	printf "    $ARG_PBITS_DETAIL   $ARG_PBITS_DETAIL_S\n"
	printf "    $ARG_USAGE   $ARG_USAGE_S\n"
}

function parse_args()
{
	argvs=($(echo "$@"))
	elements=$[ $# - 1 ]
	for (( i = 0; i <= $elements; i++ ))
	{
		# 解析抓包文件参数
		if [ ${argvs[$i]} = $ARG_USAGE ]; then
			usage
			return 1
		fi
		# 解析UNIXsocket路径参数
		if [ ${argvs[$i]} = $ARG_UNIX_PATH ]; then
			unix_path=${argvs[${i}+1]}
			#文件必须存在
			if [ ! -e $unix_path ]; then
				printf "Unix Path not exist. $unix_path\n"
				printf "TYPE>> $exe_name $ARG_USAGE for help.\n"
				return 1
			fi
			#文件必须为Socket类型
			if [ ! -S $unix_path ]; then
				printf "File must be Unix Socket Path. $unix_path\n"
				printf "TYPE>> $exe_name $ARG_USAGE for help.\n"
				return 1
			fi

		fi
		# 解析抓包文件参数
		if [ ${argvs[$i]} = $ARG_PCAP_FILE ]; then
			pcap_file=${argvs[${i}+1]}
			pcap_switch=1
			if [ -e $pcap_file ]; then
				printf "PCAP file: $pcap_file exist, overwrite it.\n"
				printf "TYPE>> $exe_name $ARG_USAGE for help.\n"
				rm -f $pcap_file
			fi
		fi

		# 显示包的比特信息
		if [ ${argvs[$i]} = $ARG_PBITS_DETAIL ]; then
			pbits_flag=1
		fi
		# 解析临时端口参数
		if [ ${argvs[$i]} = $ARG_TCP_PORT ]; then
			tcp_port=${argvs[${i}+1]}
		fi

	}
	return 0
}

if [ ! -e  /usr/bin/socat ]; then
	printf "Not socat found, install socat first.\n"
	exit 0
fi
if [ ! -e  /usr/sbin/tcpdump ]; then
	printf "Not tcpdump found, install tcpdump first.\n"
	exit 0
fi

#没有参数直接退出
if [ $# -lt 1 ]; then
	usage
	exit 0
fi

#解析参数
parse_args $*

#参数解析失败，直接退出
if [ $? -ne 0 ]; then
	exit 0
fi


unix_path_original="$unix_path.original"


# Move socket files
mv "${unix_path}" "${unix_path_original}"
trap "{ rm '${unix_path}'; mv '${unix_path_original}' '${unix_path}'; }" EXIT

#创建一个TCP监听，一个UNIXSocket监听
socat -t100 "TCP-LISTEN:${tcp_port},reuseaddr,fork" "UNIX-CONNECT:${unix_path_original}" &

#创建一个UNIX监听和一个TCP监听
socat -t100 "UNIX-LISTEN:${unix_path},mode=777,reuseaddr,fork" "TCP:localhost:${tcp_port}" &

#ARG_TCPDUMP=" -i $eth_port -netvvv "
#端口过滤
ARG_TCPDUMP=$ARG_TCPDUMP" port $tcp_port "

#是否输出抓包文件
if [ $pcap_switch = "1" ]; then
	ARG_TCPDUMP=$ARG_TCPDUMP" -w ${pcap_file}"
fi

if [ $pbits_flag = "1" ]; then
	ARG_TCPDUMP=$ARG_TCPDUMP" -x"
fi


#保存抓包数据  -i lo -netvvv -x port $tcpport -w "${pcapfile}"
tcpdump $ARG_TCPDUMP

