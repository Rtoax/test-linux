#!/bin/bash
set -e

which dpkg 2>&1 >/dev/null && dpkg --list | grep linux-image || true
which rpm 2>&1 >/dev/null && rpm -qa | grep -w kernel || true
