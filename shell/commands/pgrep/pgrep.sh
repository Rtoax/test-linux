#!/bin/bash
set -e

# command has systemd-journal
# 645 /usr/lib/systemd/systemd-journald
pgrep -a systemd-journal

# argument has rhgb
# 1 /usr/lib/systemd/systemd rhgb --switched-root --system --deserialize=35
pgrep -af rhgb
