#!/bin/bash

sudo bpftrace -l uprobe:libc:*
