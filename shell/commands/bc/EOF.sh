#!/bin/bash

b=1.1
c=2.2

a0=$(bc << EOF
	(1 + 2) * 4 / 2
EOF
	)

echo ${a0}

a1=$(bc << EOF
	d = 2
	e = $b + $c
	(d + e) * 2
EOF
	)

echo ${a1}
