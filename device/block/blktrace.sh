#!/bin/bash
sudo blktrace -d /dev/sda -a write -a read
