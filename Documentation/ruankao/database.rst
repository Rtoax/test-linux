===============
Database 数据库
===============

思维导图概览
------------

- :ref:`fig-Database-ACID`
- :ref:`fig-Database-CAP`
- :ref:`fig-Database-BASE`


ACID
--------

.. _fig-Database-ACID:

.. mermaid::
   :caption: ACID

    flowchart LR
        ACID(ACID) ==> Atomicity([Atomicity 操作原子性])
        ACID ==> Consistency([Consistency 数据一致性])
        ACID ==> Isolation([Isolation 执行隔离性])
        ACID ==> Durability([Durability 改变持续性])

        style ACID fill:#f9f,stroke:#333,stroke-width:2px


CAP 原则
--------

.. _fig-Database-CAP:

.. mermaid::
   :caption: CAP 原则

    flowchart LR
        CAP(CAP 原则) ==> Consistency([Consistency 一致性])
        CAP ==> Availavility([Availavility 可用性])
        CAP ==> Partition([Partition Tolerance 分区容错性])

        style CAP fill:#f9f,stroke:#333,stroke-width:2px


BASE 理论
---------

.. _fig-Database-BASE:

.. mermaid::
   :caption: BASE 理论

    flowchart LR
        BASE(BASE 理论) ==> BA([Basically Available 基本可用])
        BASE ==> S([Soft state 软状态])
        BASE ==> E([Eventually consistent 最终一致性])

        style BASE fill:#f9f,stroke:#333,stroke-width:2px
