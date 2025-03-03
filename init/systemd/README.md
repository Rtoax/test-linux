systemd
=========

# Q&A

## 怎么进入 shell

1. Reboot
2. 按 'e' 修改内核参数，添加`systemd.debug-shell=1`，同时可以添加`systemd.log_level=debug`，有时候添加`console=ttyS0,115200`是好的选择。
3. 按 F10 启动
4. 启动后，进入紧急模式，此时还是会显示`root account is locked`
5. 按`Alt+Ctrl+F9`进入 `tty9`，即可进入 `sh# `


## 怎么主动进入 initramfs shell

1. 添加 rd.break


## 修改 /etc/fstab

如果报只读，需要重新挂载

```
mount -o remount,rw ./mnt ./mnt
```


# Links

- https://vmware.github.io/photon/assets/files/html/3.0/photon_troubleshoot/enabling-systemd-debug.html
