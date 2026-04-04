==================
Information-System
==================

思维导图概览
------------

- :ref:`fig-Information-System`
- :ref:`fig-Nolan-Model`


信息系统
--------

.. _fig-Information-System:

.. mermaid::
   :caption: 信息系统

    flowchart LR
        Info(信息系统) ==> Summary([信息系统概述])
        Info ==> Models([典型信息系统架构模型])
        Info ==> Strategy([信息化战略体系])
        Info ==> EAI([企业应用集成*])
        Info ==> E-commerce([电子商务])

        Summary --> InfoIntroduce[信息系统介绍]
        Summary --> InfoType[信息系统分类]
        Summary --> InfoLifeCycle[信息系统生命周期]
        Summary --> InfoDevelMethod[信息系统开发方法]

        InfoIntroduce --> Nolan[诺兰模型]

        InfoType --> TPS[业务处理系统 TPS]
        InfoType --> DPS[数据处理系统 DPS]
        InfoType --> MIS[管理信息系统 MIS]
        InfoType --> DSS[决策支持系统 DSS]
        InfoType --> ES[专家系统 ES]
        InfoType --> CRM[客户关系系统 CRM]
        InfoType --> SCM[供应链管理 SCM]
        InfoType --> ERP[企业资源规划 ERP]
        InfoType --> OAS[办公自动化系统 OAS]

        InfoDevelMethod --> Method1[结构化开发方法]
        InfoDevelMethod --> Method2[面向对象开发方法]
        InfoDevelMethod --> Method3[面向服务 SOA]
        InfoDevelMethod --> Method4[原型化]

        style Info fill:#f9f,stroke:#333,stroke-width:2px
        style EAI fill:#f9f,stroke:#333,stroke-width:2px


诺兰模型
--------

.. _fig-Nolan-Model:

.. mermaid::
   :caption: 诺兰模型

    flowchart LR
        Nolan(诺兰模型) ==> Procedure1([初始阶段])
        Nolan ==> Procedure2([传播阶段])
        Nolan ==> Procedure3([控制阶段])
        Nolan ==> Procedure4([集成阶段])
        Nolan ==> Procedure5([数据管理阶段])
        Nolan ==> Procedure6([成熟阶段])
