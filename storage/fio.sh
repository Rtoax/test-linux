#!/bin/bash

fio --name=global --direct=1 --name=read --rw=read --size=10m --name=write --rw=randwrite --size=5m

