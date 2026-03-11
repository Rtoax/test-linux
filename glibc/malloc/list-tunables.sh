#!/bin/bash
set -e
ld.so --list-tunables 2>/dev/null | grep -i malloc || true
