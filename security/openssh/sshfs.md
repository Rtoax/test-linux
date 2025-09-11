sshfs
======

可以把SSH 远程登录的机器的目录挂载到本地机器上，在与远程服务器频繁进行文
件交换时非常便利。例如，将remote 主机的admin 用户的foo 目录挂载到本地的~/
remote-foo 时，命令行如下。类似一般的SSH，同样要求输入密码。

```
$ sshfs hshimamoto@remote:foo ~/remote-foo
```

Umount

```
$ fusermount3 -u ~/remote-foo
# 或
$ umount ~/remote-foo
```

