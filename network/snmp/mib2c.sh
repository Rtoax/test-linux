#!/bin/bash

S1=SYLINCOM-5G
S2=duMgmtGroup

#1、	mib2c.scalar.conf，生成scalar框架代码：
mib2c -c mib2c.scalar.conf S1::S2
#2、	mib2c.iterate.conf，生成iterate框架代码：
mib2c -c mib2c.iterate.conf S1::S2
#3、	mib2c.old-api.conf，生成oil-api框架代码：
mib2c -c mib2c.old-api.conf S1::S2

