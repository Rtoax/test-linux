Samba
=====

samba config
------------

1. 修改配置文件： /etc/samba/smb.conf

.. code-block:: text

    [自定义共享文件名]
        path = 文件夹路径，绝对路径
        public = yes|no //默认为no
        browseable = yes|no //默认为yes
        read only = yes|no //默认为yes
        write list = 用户1，用户2，。。。 //默认为无
        valid users = 用户1，用户2.。。 //默认为任何用户
        hosts allow = 客户机地址
        hosts deny = 客户机地址

示例：

.. code-block:: text

    [rongtao]
        comment = RongTao
        path = /home/rongtao/
        valid users = rongtao
        browseable = Yes
        writable = Yes
        read only = No
        write list = root rongtao
        valid users = root rongtao
        create mask = 0777
        directory mask = 0777
        available = Yes

2. 防火墙设置

.. code-block:: text

        firewall-cmd --set-default-zone=trusted


3. 添加samba共享账号

.. code-block:: text

        #这里设置的密码，即为只用windows网络驱动是输入的密码
        pdbedit -a root
        pdbedit -a rongtao
        pdbedit -L #查看共享账号

4. 当没有权限访问，那么

.. code-block:: text

        setenforce 0


samba mount
-----------

.. code-block:: text

    USERNAME=rongtao
    PASSWORD=xxxx

    mount -t cifs //REMOTE_IP/path/to/dir /mnt/smb/ -o username=$USERNAME,password=$PASSWORD
