#!/bin/bash
set -e

cat /proc/sys/crypto/fips_{name,version,enabled}
