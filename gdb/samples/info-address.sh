#!/bin/bash
make hello
gdb --quiet ./hello < info-address.gdb | grep -ow -E '0x[0-9a-fA-F]*?'
