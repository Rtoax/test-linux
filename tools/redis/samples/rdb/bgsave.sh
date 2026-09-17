#!/bin/bash
set -e

# /var/lib/valkey/dump.rdb
redis-cli bgsave
