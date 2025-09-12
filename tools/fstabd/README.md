fstabd
======

> 建议使用 scripts/ 下的程序，C语言程序实现的有点蹩脚.

监控 /etc/fstab 的修改并检测其合法性，若不合法的修改，此次修改将不起作用。


# 安装

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
$ sudo systemctl start fstabd.service
$ sudo systemctl status fstabd.service
```


# 查看日志

```bash
$ journalctl -xeu fstabd.service
```


# 卸载

```bash
$ sudo systemctl stop fstabd.service
$ cd build
$ sudo make uninstall
```

