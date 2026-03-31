#!/bin/bash
set -e

# List all builtin modules
cat /lib/modules/$(uname -r)/modules.builtin
