=======
Grafana
=======

default port is `3000`, http://localhost:3000.

安装`grafana`

.. code-block:: shell

    sudo dnf install grafana.x86_64
    sudo systemctl start grafana-server.service
    sudo systemctl status grafana-server.service

配置：

1. 配置 Prometheus 为数据源
2. 选择仪表盘 https://grafana.com/grafana/dashboards/


Links
-----

- https://grafana.org
