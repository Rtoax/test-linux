Redis
=====

Licenses
--------

.. list-table::
   :widths: 15 15
   :header-rows: 1

   * - Redis Version
     - License
   * - 7.4+
     - RSALv2/SSPL
   * - 7.2.4
     - BSD


Data Types
----------

.. list-table::
   :widths: 15 15
   :header-rows: 1

   * - Type
     - Operations
   * - list
     -
   * - hash
     -
   * - set
     -
   * - zset
     - ZADD, ZRANGE


Redis Persistence
-----------------

RDB - Redis Database Backup file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

AOF - Append Only File
~~~~~~~~~~~~~~~~~~~~~~

Configuration file `/etc/redis/redis.conf`, `/etc/valkey/valkey.conf`.

Enable AOF:

.. code-block:: text

    appendonly yes
    appendfilename "appendonly.aof"

AOF recording frequency:

.. code-block:: text

    appendfsync always
    appendfsync everysec
    appendfsync no


Benchmark
---------

Links
-----

- Redis 官网: https://redis.io/
- Redis 源码地址: https://github.com/redis/redis
- Redis 命令参考: http://doc.redisfans.com/
- https://www.runoob.com/redis/redis-tutorial.html
