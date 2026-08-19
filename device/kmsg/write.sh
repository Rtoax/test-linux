#!/bin/bash
set -e

date | sudo tee /dev/kmsg
cat /etc/os-release | sudo tee /dev/kmsg
