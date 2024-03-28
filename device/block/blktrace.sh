#!/bin/bash
sudo blktrace -d /dev/sda -a write -a read

# Same as: btrace /dev/sda
sudo blktrace -d /dev/sda -o - | blkparse -i -

