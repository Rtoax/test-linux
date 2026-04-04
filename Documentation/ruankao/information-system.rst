===========================
Information System 信息系统
===========================

思维导图概览
------------

- :ref:`fig-Information-System`
- :ref:`fig-Nolan-Model`
- :ref:`fix-Structured-development-method`


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

        Models --> Model1[政府信息化和电子政务]

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

        InfoLifeCycle --> Cycle1[产生阶段]
        InfoLifeCycle --> Cycle2[开发阶段]
        InfoLifeCycle --> Cycle3[运行阶段]
        InfoLifeCycle --> Cycle4[消亡阶段]

        InfoDevelMethod --> Method1[结构化开发方法]
        InfoDevelMethod --> Method2[面向对象方法 OOA]
        InfoDevelMethod --> Method3[面向服务方法 SOA]
        InfoDevelMethod --> Method4[原型化方法]

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

        style Nolan fill:#f9f,stroke:#333,stroke-width:2px


结构化开发方法
--------------

.. _fix-Structured-development-method:

.. mermaid::
   :caption: 结构化开发方法

    flowchart LR
        Structured(结构化开发方法) ==> Essence([精髓])
        Structured ==> Procedure([主要阶段])
        Structured ==> Features([主要特点])
        Structured ==> Disadvantage([不足和局限])
        Structured ==> Tools([常用工具])

        Essence --> Essence1[自顶向下]
        Essence --> Essence2[逐步求精]
        Essence --> Essence3[模块化设计]

        Procedure --> Procedure1[需求分析阶段]
        Procedure --> Procedure2[概要设计阶段]
        Procedure --> Procedure3[详细设计阶段]
        Procedure --> Procedure4[编码实现阶段]
        Procedure --> Procedure5[测试阶段]
        Procedure --> Procedure6[部署阶段]

        Features --> Features1[开发目标清晰化]
        Features --> Features2[开发工作阶段化]
        Features --> Features3[开发文档规范化]
        Features --> Features4[设计方法结构化]

        Disadvantage --> Disadvantage1[开发周期长]
        Disadvantage --> Disadvantage2[难以适应需求变化]
        Disadvantage --> Disadvantage3[很少考虑数据结构]

        Tools --> Tool1[数据流图 DFD]
        Tools --> Tool2[数据字典]
        Tools --> Tool3[结构化语言]
        Tools --> Tool4[判定表]
        Tools --> Tool5[判定树]

        style Structured fill:#f9f,stroke:#333,stroke-width:2px
