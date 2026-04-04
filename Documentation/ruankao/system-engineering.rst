==================
System Engineering
==================

思维导图概览
------------

- :ref:`fig-System-Engineering`


系统工程
--------

.. _fig-System-Engineering:

.. mermaid::
   :caption: 系统工程

    flowchart LR
        Engineering(系统工程) ==> Concept([基本概念])
        Engineering ==> Huoer([霍尔三维结构])
        Engineering ==> Qieke([切克兰德方法])
        Engineering ==> Bingxing([并行工程方法])
        Engineering ==> Zonghe([综合集成法])
        Engineering ==> WSR([WSR 物理-事理-人理 系统方法])

        Huoer --> Huoer1[时间维]
        Huoer --> Huoer2[逻辑维]
        Huoer --> Huoer3[知识维]

        Qieke --> QiekeProcedure[七个步骤]

        QiekeProcedure --> QiekeProcedure1[认识问题]
        QiekeProcedure --> QiekeProcedure2[根底定义]
        QiekeProcedure --> QiekeProcedure3[建立概念模型]
        QiekeProcedure --> QiekeProcedure4[比较和探索]
        QiekeProcedure --> QiekeProcedure5[选择]
        QiekeProcedure --> QiekeProcedure6[设计与实施]
        QiekeProcedure --> QiekeProcedure7[评估与反馈]

        style Engineering fill:#f9f,stroke:#333,stroke-width:2px
