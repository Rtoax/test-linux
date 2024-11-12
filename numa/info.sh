#!/bin/bash
set -e

sudo dmesg | grep -E 'node   [0-9]'
