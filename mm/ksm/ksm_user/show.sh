#!/bin/bash

set -euo pipefail
echo "/sys/kernel/mm/ksm/pages_sharing"
cat /sys/kernel/mm/ksm/pages_sharing

echo "/sys/kernel/mm/ksm/pages_shared"
cat /sys/kernel/mm/ksm/pages_shared

echo "/sys/kernel/mm/ksm/pages_unshared"
cat /sys/kernel/mm/ksm/pages_unshared

# 可以使用 watch -n1 sh show.sh 指令执行查看
