Namespace
=========

* `Namespace` 资源的隔离
* `CGroups` 资源的限制


| Namespace | enum            | 隔离内容 |
| --------- | --------------- | ------- |
| Cgroup    | CLONE_NEWCGROUP | Cgroup root directory |
| IPC       | CLONE_NEWIPC    | System V IPC, POSIX消息队列 |
| Network   | CLONE_NEWNET    | 网络设备、栈、端口等 |
| Mount     | CLONE_NEWNS     | 挂载点 |
| PID       | CLONE_NEWPID    | 进程ID |
| User      | CLONE_NEWUSER   | 用户和组ID |
| UTS       | CLONE_NEWUTS    | 主机名和NIS域名 |
