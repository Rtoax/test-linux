#!/bin/bash
set -e

sudo find -type d -exec chmod +x {} \;
sudo find -type f -name '*.sh' -exec chmod +x {} \;
