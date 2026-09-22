#!/bin/bash
set -e

# = git log -1 --oneline --name-only --pretty=format:
git show --name-only --pretty=format:
# = git log -1 --name-status --pretty=format:
git show --name-status --pretty=format: -M HEAD
