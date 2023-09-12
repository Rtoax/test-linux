#!/bin/bash
lspci -vmmk | grep -i nvme -A 10 -B 10
