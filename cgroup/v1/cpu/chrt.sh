#!/bin/bash
set -e

FS=/sys/fs/cgroup/

sudo mkdir ${FS}/cpu/testa/ || true

echo $$ | sudo tee ${FS}/cpu/testa/tasks
echo 0 | sudo tee ${FS}/cpu/testa/cpu.rt_runtime_us

# Should: chrt: failed to set pid 0's policy: Operation not permitted
error=$( sudo chrt -f 99 ls 2>&1 | grep -o 'Operation not permitted' || true )
if [[ "${error}" != "Operation not permitted" ]]; then
	echo "ERROR: failed test chrt"
fi

# Move task to root cpu cgroup
echo $$ | sudo tee ${FS}/cpu/tasks
sudo rmdir ${FS}/cpu/testa
