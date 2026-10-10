journalctl
==========

命令行
------

* 查看所有日志：默认情况下，只保存本次启动的日志

.. code-block:: shell

   journalctl

* 查看内核日志（不显示应用日志）

.. code-block:: shell

   journalctl -k

* 查看系统本次启动的日志

.. code-block:: shell

   journalctl  -b
   journalctl  -b  -0

* 查看上一次启动的日志

需更改设置,如上次系统崩溃，需要查看日志时，就要看上一次的启动日志。

.. code-block:: shell

   journalctl  -b -1

* 查看指定时间的日志

.. code-block:: shell

   journalctl --since="2012-10-3018:17:16"
   journalctl --since "20 minago"
   journalctl --since yesterday
   journalctl --since"2015-01-10" --until "2015-01-11 03:00"
   journalctl --since 09:00 --until"1 hour ago"
   journalctl --since"15:15" --until now

* 显示尾部的最新10行日志

.. code-block:: shell

   journalctl  -n

* 显示尾部指定行数的日志

查看的是/var/log/messages的日志，但是格式上有所调整，如主机名格式不一样而已

.. code-block:: shell

   journalctl -n 20

* 实时滚动显示最新日志

.. code-block:: shell

   journalctl   -f

* 查看指定服务的日志

.. code-block:: shell

   journalctl  /usr/lib/systemd/systemd

* 查看指定进程的日志

.. code-block:: shell

   journalctl   _PID=1

* 查看某个路径的脚本的日志

.. code-block:: shell

   journalctl    /usr/bin/bash

* 查看指定用户的日志

.. code-block:: shell

   journalctl _UID=33  --since today


* 查看某个Unit的日志

.. code-block:: shell

   journalctl  -u nginx.service
   journalctl  -u nginx.service  --since  today


* 实时滚动显示某个Unit的最新日志

.. code-block:: shell

   journalctl  -u nginx.service  -f


* 合并显示多个Unit的日志

.. code-block:: shell

   journalctl  -u nginx.service  -u php-fpm.service  --since today


* 查看指定优先级（及其以上级别）的日志

日志优先级共有8级

- 0: emerg
- 1: alert
- 2: crit
- 3: err
- 4: warning
- 5: notice
- 6: info
- 7: debug

.. code-block:: shell

   journalctl -p err -b


* 不分页标准输出

日志默认分页输出--no-pager改为正常的标准输出

.. code-block:: shell

   journalctl  --no-pager


* 以JSON格式（单行）输出

以JSON格式（单行）输出

.. code-block:: shell

   journalctl  -b -u httpd.service  -o json


* 以JSON格式（多行）输出，可读性更好，建议选择多行输出

.. code-block:: shell

   journalctl  -b -u httpd.service  -o json-pretty


* 显示日志占据的硬盘空间

.. code-block:: shell

   journalctl  --disk-usage


* 指定日志文件占据的最大空间

.. code-block:: shell

   journalctl   --vacuum-size=1G


* 指定日志文件保存多久

.. code-block:: shell

   journalctl   --vacuum-time=1years


参考链接
--------

* journalctl 日志查看方法: https://www.cnblogs.com/leigepython/p/10302056.html
