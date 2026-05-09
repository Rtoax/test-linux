#!/bin/bash
set -e
. start-redis-server.sh

redis-cli ping
