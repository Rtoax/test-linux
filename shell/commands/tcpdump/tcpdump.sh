#!/bin/bash

interface=
pcap_file=

# Port: only one
port=
src_port=
dst_port=

reset_cmd() {
	interface=
	pcap_file=
	port=
	src_port=
	dst_port=
}

generate_cmd() {
	local -a args

	[[ -z $interface ]] && interface=any

	[[ ! -z ${pcap_file} ]] && args+=( -w ${pcap_file} )
	[[ ! -z ${port} ]] && args+=( port ${port} )
	[[ ! -z ${src_port} ]] && args+=( src port ${src_port} )
	[[ ! -z ${dst_port} ]] && args+=( src port ${dst_port} )

	args+=( -i $interface )
	args+=( -up )

	COMMAND="sudo tcpdump ${args[@]}"
	echo $COMMAND
}

reset_cmd
port=22
generate_cmd

reset_cmd
port=22
pcap_file=a.pcap
generate_cmd
