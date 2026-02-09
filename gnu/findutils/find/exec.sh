#!/bin/bash
set -e

sudo find -type d -exec chmod 755 {} \;
sudo find -type f -exec chmod 644 {} \;
