#!/bin/bash

#初始化
sudo service postgresql initdb

#启动服务
sudo service postgresql start

#查看状态
sudo service postgress status

#连接用户和数据库
#$ sudo su - username
#$ psql databasename
# databasename=#
