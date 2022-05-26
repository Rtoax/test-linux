#!/bin/bash

pid=1
perf kvm --host -o perf.data stat record -p $pid
perf kvm -i perf.data stat report
