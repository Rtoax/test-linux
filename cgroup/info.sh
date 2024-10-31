#!/bin/bash
set -e

systemctl --version

cat /proc/filesystems | grep cgroup

lscgroup

cat /proc/$$/cgroup

