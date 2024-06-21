#!/bin/bash

sudo bpftrace  -e 'BEGIN{$min = kaddr("node_reclaim_mode"); printf("node_reclaim_mode = %d\n", *$min);}'
