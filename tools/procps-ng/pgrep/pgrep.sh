#!/bin/bash
set -e

# command has systemd-journal
# 645 /usr/lib/systemd/systemd-journald
pgrep -a systemd-journal

# argument has 'user'
# 1 /usr/lib/systemd/systemd --user
pgrep -af user
