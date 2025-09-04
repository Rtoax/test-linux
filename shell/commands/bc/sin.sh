#!/bin/bash

readonly PI=3.1415926535897932

for i in {0..90}; do
	x=$(echo "scale=2; $i * ${PI} / 180.0" | bc)
	sin_val=$(echo "s($x)" | bc -l)
	echo "sin($x<$i>) = $sin_val"
done
