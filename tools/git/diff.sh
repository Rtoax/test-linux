#!/bin/bash
set -e

git diff --stat --name-only HEAD^ HEAD

# Generate patch between two tags or two commits
git diff v2.4.6-Kappa v2.4.8-Memory > v2.4.6-v2.4.8.patch
git diff v2.4.6-Kappa v2.4.8-Memory ../../Makefile > v2.4.6-v2.4.8-Makefile.patch
git diff cd04f2f29bb6 dcbc5cf45eb1 > os-almalinux-kylin-opencloudos.patch
