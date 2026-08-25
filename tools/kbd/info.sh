#!/bin/bash
set -e

# text, etc.
sudo kbdinfo getmode
# unicode, etc.
sudo kbdinfo gkbmode
# escprefix, etc.
sudo kbdinfo gkbmeta

sudo showconsolefont
