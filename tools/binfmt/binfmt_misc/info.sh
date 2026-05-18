#!/bin/bash
set -e

sudo cat /proc/sys/fs/binfmt_misc/status
ls /proc/sys/fs/binfmt_misc/
