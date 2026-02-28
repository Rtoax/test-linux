#!/bin/bash
make fork
gdb --quiet ./fork -x follow-fork-mode.gdb
gdb --quiet ./fork -x detach-on-fork.gdb
