#!/bin/bash
set -e

# fuser use stdin,stderr at the same time
exec 2>&1

fuser -mv /
