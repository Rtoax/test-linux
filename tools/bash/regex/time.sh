#!/bin/bash

echo "=== Match 00:00"
cat time.txt | egrep "^(([0-9]|[0-9]\\w+)\\:([0-9]|[0-9]\\w+)){1,1}$"

echo "=== Match 00:00:00"
cat time.txt | egrep "^(([0-9]|[0-9]\\w+)\\:){2,2}([0-9]|[0-9]\\w+)$"

echo "=== Match 00-00:00:00"
cat time.txt | egrep "^([0-9]|[0-9]\\w+)\\-(([0-9]|[0-9]\\w+)\\:){2,2}[0-9]\\w+$"

