#!/bin/bash
set -e

sudo ls -l /proc/self/ns/net
sudo unshare --net --fork ls -l /proc/self/ns/net
