#!/bin/bash

export S_TIME_FORMAT=ISO

echo -e "CPU\t%user\t%sys\t%irq\t%soft\t%idle"
mpstat -P ALL 2 | \
	grep -v soft | \
	grep -v all | \
	grep -v $(uname -r) | \
	awk '{
		if ($3>4.00 || $5>4.00 || $7>4.00 || $8>4.00)
			print $2"\t"$3"\t"$5"\t"$7"\t"$8"\t"$12
		}'
