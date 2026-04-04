===============
Database 数据库
===============

思维导图概览
------------

- :ref:`fig-Database-Design`
- :ref:`fig-Database-ACID`
- :ref:`fig-Database-CAP`
- :ref:`fig-Database-BASE`


数据库设计
----------

.. _fig-Database-Design:

.. mermaid::
   :caption: 数据库设计

    flowchart LR
        DB(数据库设计概述) ==> Concept([数据库系统概念])
        DB ==> Model([数据模型])
        DB ==> RelationalAlgebra([关系代数])
        DB ==> SQL([SQL])
        DB ==> Norm([规范化])
        DB ==> Control([数据库的控制])
        DB ==> Other([其他知识])

        Concept --> Concept1[数据库系统概述]
        Concept --> Concept2[三级模型两级映射]
        Concept --> Design[数据库设计]

        Concept1 --> DBS[数据库系统 DBS]
        Concept1 --> DBMS[数据库管理系统 DBMS]

        Concept2 --> ExternalLevel[外模式]
        Concept2 --> Image1([外模式/概念模式映像])
        Concept2 --> ConceptualLevel[概念模式]
        Concept2 --> Image2([概念模式/内模式映像])
        Concept2 --> InternalLevel[内模式]

        ExternalLevel --> ExternalLevel1[面向应用程序: View]
        ConceptualLevel --> ConceptualLevel1[面向数据库设计人员: 逻辑结构]
        InternalLevel --> InternalLevel1[磁盘存储]

        Design --> Design1[需求分析] --> Design11[数据流图，数据字典，需求说明书]
        Design --> Design2[概念结构设计] --> Design21[E-R 图]
        Design --> Design3[逻辑结构设计] --> Design31[关系模式]
        Design --> Design4[物理设计]
        Design --> Design5[数据库实施阶段]
        Design --> Design6[数据库运行和维护阶段]

        Model --> E-R[E-R 模型]
        Model --> Model2[关系模型]

        Norm --> Norm1[函数依赖]
        Norm --> Norm2[键与约束]
        Norm --> Norm3[规范化的三范式]
        Norm --> Norm4[模式分解]
        Norm --> Norm5[反规范化]

        Control --> Transaction[事物]
        Control --> Concurrency[并发控制]
        Control --> Blockade[封锁协议]

        Other --> App[应用程序与数据库的交互]
        Other --> NoSQL[NoSQL 数据库]


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
