#!/bin/bash

sudo trace-cmd list -f clone | grep clone | grep sys
sudo trace-cmd record -g __x64_sys_clone -p function_graph
sudo trace-cmd report | more
