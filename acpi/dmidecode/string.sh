#!/bin/bash

# dmidecode(8)
strings=(
bios-vendor bios-version bios-release-date bios-revision firmware-revision system-manufacturer
system-product-name system-version system-serial-number system-uuid system-sku-number system-family
baseboard-manufacturer baseboard-product-name baseboard-version baseboard-serial-number
baseboard-asset-tag chassis-manufacturer chassis-type chassis-version chassis-serial-number
chassis-asset-tag processor-family processor-manufacturer processor-version processor-frequency
)

for s in ${strings[@]}
do
	printf "%-32s %s\n" $s "$(sudo dmidecode -s $s)"
done
