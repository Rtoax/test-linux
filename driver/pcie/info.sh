#!/bin/bash

slot_vendor() {
	slots=( $(lspci -n | awk '{print $1}') )

	declare -a n_vendors s_vendors

	for slot in ${slots[@]}
	do
		s_vendor="$(lspci -vmm -s ${slot} | grep ^Vendor | sed 's/Vendor://g' | tr -d '\t')"
		s_vendors+=( "${s_vendor}" )
		n_vendor="$(lspci -vmm -s ${slot} -n | grep ^Vendor | sed 's/Vendor://g' | tr -d '\t')"
		n_vendors+=( ${n_vendor} )
	done

	printf "%-16s %-8s %s\n" SLOT VENDOR VENDOR
	for ((i = 0; i < ${#slots[@]}; i++))
	do
		printf "%-16s %-8s %s\n" ${slots[$i]} ${n_vendors[$i]} "${s_vendors[$i]}"
	done
}

pcie_tree() {
	lspci -tv
}

pcie_tree
