Samba config
============

1. 修改配置文件： /etc/samba/smb.conf

[自定义共享文件名]
	path = 文件夹路径，绝对路径
	public = yes|no //默认为no
	browseable = yes|no //默认为yes
	read only = yes|no //默认为yes
	write list = 用户1，用户2，。。。 //默认为无
	valid users = 用户1，用户2.。。 //默认为任何用户
	hosts allow = 客户机地址
	hosts deny = 客户机地址

2. 防火墙设置

	firewall-cmd --set-default-zone=trusted

3. 添加samba共享账号

	#这里设置的密码，即为只用windows网络驱动是输入的密码
	pdbedit -a root
	pdbedit -a rongtao
	pdbedit -L #查看共享账号

4. 当没有权限访问，那么

	setenforce 0
