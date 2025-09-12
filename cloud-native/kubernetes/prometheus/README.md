Prometheus
==========

# 配置 Prometheus 简述

## 客户端

安装`node-exporter`

```bash
sudo dnf install golang-github-prometheus-node-exporter
```

启动node-exporter服务：

```bash
sudo systemctl start node-exporter.service
```

> fedora37 中服务名为 node-exporter.service
> centos-stream9 中服务名为 prometheus-node-exporter.service

默认打开`9100`端口（如上`scrape_configs:`的`targets:`所示）。


## 服务端

安装`prometheus`

```bash
sudo dnf install golang-github-prometheus
```

配置中添加 job

`/etc/prometheus/prometheus.yml`

```yaml
scrape_configs:
  - job_name: 'pc-vm-fedora37'
    static_configs:
      - targets: ['192.168.122.20:9100']
```

启动或重启 prometheus.service

```bash
sudo systemctl start prometheus.service
```


# 前端 grafana 仪表盘

安装`grafana`

```bash
sudo dnf install grafana.x86_64
sudo systemctl start grafana-server.service
sudo systemctl status grafana-server.service
```

配置：

1. 配置 Prometheus 为数据源
2. 选择仪表盘 [仪表盘市场](https://grafana.com/grafana/dashboards/)


# Node-exporter限额

```bash
# '#' 为注释或命令行输出
# 查看控制器
cat /sys/fs/cgroup/cgroup.controllers
# cpuset cpu io memory hugetlb pids misc

# 创建 node-exporter cgroup
mkdir /sys/fs/cgroup/node-exporter

# 为 node-exporter cgroup 添加 cpuset 控制器
echo "+cpu"    >> /sys/fs/cgroup/node-exporter/cgroup.subtree_control
echo "+cpuset" >> /sys/fs/cgroup/node-exporter/cgroup.subtree_control
#  如果上面命令执行失败，再执行
echo "+cpuset" >> /sys/fs/cgroup/cgroup.subtree_control

# 再创建一个子 cgroup，并添加cpu/cpuset控制器
mkdir /sys/fs/cgroup/node-exporter/tasks
echo "+cpu"    >> /sys/fs/cgroup/node-exporter/tasks/cgroup.subtree_control
echo "+cpuset" >> /sys/fs/cgroup/node-exporter/tasks/cgroup.subtree_control

# 查看pid，并将pid加入cgroup
pidof prometheus-node-exporter
# 1050
echo 1050 >> /sys/fs/cgroup/node-exporter/tasks/cgroup.procs

# 查看当前限额
cat /sys/fs/cgroup/node-exporter/tasks/cpu.max
# max 100000
#  max 表示无限额： max 100000 分别为 quota 和 period。

# 设置限额
#  200000 1000000 ~= 20%
#    2000 1000000 ~= 0.2%
#    1000 1000000 ~= 0.1% (这种CPU配额，prometheus查不到node-exporter内容)
#                         (重新增加配额，可恢复通信)
echo "200000 1000000" > /sys/fs/cgroup/node-exporter/tasks/cpu.max
```
