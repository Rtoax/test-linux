#!/bin/bash

sudo grep ' dump_vmcs' /proc/kallsyms | awk '/dump_vmcs\t/'

