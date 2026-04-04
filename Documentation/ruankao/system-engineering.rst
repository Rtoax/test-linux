===========================
System Engineering 系统工程
===========================

思维导图概览
------------

- :ref:`fig-System-Engineering`
- :ref:`fig-System-Engineering-LifeCycle`
- :ref:`fig-System-Engineering-LifeCycle-Method`
- :ref:`fig-MBSE`


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


系统工程生命周期
----------------

.. _fig-System-Engineering-LifeCycle:

.. mermaid::
   :caption: 系统工程生命周期

    flowchart LR
        LifeCycle(系统工程生命周期) ==> LifeCycle1([探索性研究阶段])
        LifeCycle(系统工程生命周期) ==> LifeCycle2([概念阶段])
        LifeCycle(系统工程生命周期) ==> LifeCycle3([开发阶段])
        LifeCycle(系统工程生命周期) ==> LifeCycle4([生产阶段])
        LifeCycle(系统工程生命周期) ==> LifeCycle5([使用阶段])
        LifeCycle(系统工程生命周期) ==> LifeCycle6([保障阶段])
        LifeCycle(系统工程生命周期) ==> LifeCycle7([退役阶段])

        style LifeCycle fill:#f9f,stroke:#333,stroke-width:2px


系统工程生命周期方法
--------------------

.. _fig-System-Engineering-LifeCycle-Method:

.. mermaid::
   :caption: 系统工程生命周期方法

    flowchart LR
        Method(系统工程生命周期方法) ==> Method1([计划驱动方法])
        Method(系统工程生命周期方法) ==> Method2([渐进迭代式开发])
        Method(系统工程生命周期方法) ==> Method3([精益开发])
        Method(系统工程生命周期方法) ==> Method4([敏捷开发])

        style Method fill:#f9f,stroke:#333,stroke-width:2px


基于模型的系统工程 MBSE
------------------------

.. _fig-MBSE:

.. mermaid::
   :caption: 基于模型的系统工程 MBSE

    flowchart LR
        MBSE(基于模型的系统工程 MBSE) ==> Procedure([三个阶段])
        MBSE ==> Zhizhu([三大支柱])

        Procedure --> RequirementsAnalysis([需求分析阶段])
        Procedure --> FunctionalAnalysis([功能分析与分配阶段])
        Procedure --> Design([设计综合阶段])

        RequirementsAnalysis --> RequirementsAnalysis1[需求图]
        RequirementsAnalysis --> RequirementsAnalysis2[用例图]
        RequirementsAnalysis --> RequirementsAnalysis3[包图]

        FunctionalAnalysis --> FunctionalAnalysis1[顺序图]
        FunctionalAnalysis --> FunctionalAnalysis2[活动图]
        FunctionalAnalysis --> FunctionalAnalysis3[状态机图]

        Design --> Design1[模块定义图]
        Design --> Design2[内部块图]
        Design --> Design3[参数图]

        Zhizhu --> Zhizhu1[建模语言]
        Zhizhu --> Zhizhu2[建模工具]
        Zhizhu --> Zhizhu3[建模思路]

        style MBSE fill:#f9f,stroke:#333,stroke-width:2px
