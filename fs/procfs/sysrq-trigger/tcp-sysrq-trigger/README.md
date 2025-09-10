从客户端将 单个字符写入 服务端 `/proc/sysrq-trigger`

# 功能描述

* 服务端 

```bash
sudo ./server
```

* 客户端

```bash
./client <IP>
Input: h
```

上述实例相当于在服务端服务器执行 

```bash 
echo h > /proc/sysrq-trigger 
```

# 完整的客户端日志

```bash
$ ./trigger-slave 10.255.238.179
CMD>> 
  echo [cmd] > /proc/sysrq-trigger
   [cmd]:
    0 - loglevel 0
    1 - loglevel 1
    2 - loglevel 2
    3 - loglevel 3
    4 - loglevel 4
    5 - loglevel 5
    6 - loglevel 6
    7 - loglevel 7
    8 - loglevel 8
    9 - loglevel 9
    h - help
    b - reboot
    c - crash
    e - terminate all tasks
    f - memory full OOM kill
    i - Kill all tasks
    j - thaw filesystems
    k - sak
    l - show basktrace all active cpus
    m - show memory usage
    n - nice all RT tasks
    o - poweroff
    p - show registers
    q - show all timers
    r - unraw
    s - sync
    t - show task states
    u - unmount
    V - force fb
    w - show blocked tasks
    z - dump ftrace buffer
  Extra COMMAND:
    HELP - show this message.
    WRITEFILE - test write file to /tmp/tcp-proc-trigger-writefile.txt
CMD>> 
```
