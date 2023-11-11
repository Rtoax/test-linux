如何解决恼人的 TIME_WAIT 问题
=============================


从 TCP 状态图中可以看到，主动关闭的一方会进入 `TIME_WAIT` 状态（而被动关闭的一
方会进入 `CLOSE_WAIT` 状态）。`TIME_WAIT` 状态之所以存在是为了解决网络中的异常
问题，比如:

- 网络存在延迟和重传，前一个连接的延迟数据包可能被新的连接错误接收。
- 关闭连接时最后的 ACK 可能会丢失重传，这会干扰新的连接。
- `TIME_WAIT` 连接数量多了以后，会导致三个危害：

* 占用内存
* 占用端口号
* 占用连接跟踪表


## 解决方法

1. 增大 `net.ipv4.tcp_max_tw_buckets` 和 `net.netfilter.nf_conntrack_max`。
2. 减小 `net.ipv4.tcp_fin_timeout` 和 `net.netfilter.nf_conntrack_tcp_timeout_time_wait` ，让系统尽快释放资源。
3. 开启端口复用 `net.ipv4.tcp_tw_reuse`, 这样，被 `TIME_WAIT` 状态占用的端口，还能用到新建的连接中。
4. 增大本地端口的范围 `net.ipv4.ip_local_port_range`
5. 增加最大文件描述符的数量。你可以使用 `fs.nr_open` 和 `fs.file-max`。


# Links

- https://feisky.xyz/posts/2020-06-06-linux-perf/

