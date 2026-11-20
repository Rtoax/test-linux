#!/bin/bash
set -e

systemctl --version

cat /proc/filesystems | grep cgroup

if which lscgroup 2>/dev/null; then
	lscgroup
fi

cat /proc/$$/cgroup

