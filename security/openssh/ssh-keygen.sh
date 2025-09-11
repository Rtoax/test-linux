#!/bin/bash

# https://www.jianshu.com/p/dd053c18e5ee

# 在 .ssh 中生成密钥对 id_rsa, id_rsa.pub, 一个为公钥，一个为私钥
ssh-keygen

# 参数
# -t rsa 采用 rsa 加密方式
# -b 1024 采用长度为 1024bit 的密钥对，最长 4096
# -f 生成文件名，f=keyfilename
# -C 备注，C=comment
ssh-keygen -t rsa -b 1024 -f 10.32.161.216.ssh_key -C "comment"

# 在服务器上安装公钥密钥
cat id_rsa.pub >> ~/.ssh/authorized_keys

# 修改 /etc/ssh/sshd_config
RSAAuthentication yes
PubkeyAuthentication yes
# no - 禁止root登录
PermitRootLogin yes
# 允许密码登录，根据你的情况设置
PasswordAuthentication yes
