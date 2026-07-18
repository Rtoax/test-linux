==========
Prometheus
==========

default port is `9090`, http://localhost:9090.

配置 Prometheus 简述
--------------------

客户端
~~~~~~

:doc:`安装 node-exporter <node-exporter>`


服务端
~~~~~~

安装 `prometheus`

.. code-block:: shell

    sudo dnf install golang-github-prometheus

配置中添加 job

`/etc/prometheus/prometheus.yml`

.. code-block:: yaml

    scrape_configs:
      - job_name: 'pc-vm-fedora37'
        static_configs:
          - targets: ['192.168.122.20:9100']

启动或重启 prometheus.service

.. code-block:: shell

    sudo systemctl start prometheus.service


前端 grafana 仪表盘
-------------------

:doc:`参见 grafana <grafana>`

Node-exporter限额
-----------------

:doc:`Node-exporter限额 <node-exporter>`
