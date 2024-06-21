#!/bin/bash

sudo bpftrace  -e 'BEGIN{$min = kaddr("node_reclaim_distance"); printf("node_reclaim_distance = %d\n", *$min);}'
