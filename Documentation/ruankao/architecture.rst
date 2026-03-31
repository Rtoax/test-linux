============================
System Architecture Designer
============================

思维导图概览
------------

软件工程
~~~~~~~~

- :ref:`fig-Software-Engineering`
- :ref:`fig-Software-process-model`
- :ref:`fig-software-lifecycle`
- :ref:`fig-Reverse-engineering`


软件工程
--------

.. _fig-Software-Engineering:

.. mermaid::
   :caption: 软件工程概述

    flowchart LR
        Engineering(软件工程概述) ==> Concept([基本概念])
        Engineering ==> Maturity([软件成熟度模型])

        Concept --> Concept1[定义]
        Concept --> Concept2[软件工程活动]
        Concept --> Concept3[软件工具分类]

        Maturity --> Maturity1[CMM: 能力成熟度模型]
        Maturity --> Maturity2[CMMI: 能力成熟度模型集成]

        style Engineering fill:#f9f,stroke:#333,stroke-width:2px


.. _fig-Software-process-model:

.. mermaid::
   :caption: 软件过程模型

    flowchart LR
        Process(软件过程模型) ==> Traditional([传统模型])
        Process ==> Agile([敏捷模型])
        Process ==> Other([其他模型])

        Traditional --> Traditional1[瀑布模型]
        Traditional --> Traditional2[原型模型]
        Traditional --> Traditional3[螺旋模型]
        Traditional --> Traditional4[V模型]

        Agile --> Agile1[核心思想]
        Agile --> Agile2[4大价值观]
        Agile --> Agile3[5大原则]
        Agile --> Agile4[12个最佳实践]
        Agile --> Agile5[典型方法]

        Agile2 --> Agile21[沟通]
        Agile2 --> Agile22[简单]
        Agile2 --> Agile23[反馈]
        Agile2 --> Agile24[勇气]

        Agile3 --> Agile31[快速反馈]
        Agile3 --> Agile32[简单性假设]
        Agile3 --> Agile33[逐步修改]
        Agile3 --> Agile34[提倡更改]
        Agile3 --> Agile35[优质工作]

        Agile5 --> Agile51[极限编程XP]
        Agile5 --> Agile52[水晶系列方法]
        Agile5 --> Agile53[并列争球法Scrum]
        Agile5 --> Agile54[特性驱动开发方法FDD]

        Other --> Other1[增量模型]
        Other --> Other2[喷泉模型]
        Other --> RUP[RUP:统一过程模型]
        Other --> Other4[净室软件工程]
        Other --> Other5[基于构件的软件工程CBSE]

        RUP --> RUP1[9个工作流]
        RUP --> RUP2[4个阶段]
        RUP --> RUP3[核心特点]
        RUP --> RUP4[4+1视图]

        RUP1 --> RUP11[业务建模]
        RUP1 --> RUP12[需求]
        RUP1 --> RUP13[分析与设计]
        RUP1 --> RUP14[实现]
        RUP1 --> RUP15[测试]
        RUP1 --> RUP16[部署]
        RUP1 --> RUP17[配置与变更管理]
        RUP1 --> RUP18[项目管理]
        RUP1 --> RUP19[环境]

        RUP2 --> RUP21[初始阶段]
        RUP2 --> RUP22[细化节点]
        RUP2 --> RUP23[构造阶段]
        RUP2 --> RUP24[移交阶段]

        style Process fill:#f9f,stroke:#333,stroke-width:2px


.. _fig-software-lifecycle:

.. mermaid::
   :caption: 软件生命周期

    flowchart LR
        lifecycle(软件生命周期) ==> define([软件定义时期])
        lifecycle ==> devel([软件开发时期])
        lifecycle ==> run([软件运行维护时期])

        define --> define1[可行性研究]
        define --> define2[需求工程]

        define2 --> define21[需求分类]
        define2 --> define22[需求获取]
        define2 --> define23[需求分析]
        define2 --> define24[需求定义]
        define2 --> define25[需求验证]
        define2 --> define26[需求管理]

        define23 --> define231[目的]
        define23 --> define232[步骤]
        define23 --> define233[方法]

        define233 --> define2331[结构化方法]
        define233 --> define2332[面向对象分析方法]

        define2331 --> define23311[特点]
        define2331 --> define23312[三大模型]
        define2331 --> define23313[数据流图]

        define26 --> define261[变更控制]
        define26 --> define262[版本控制]
        define26 --> define263[需求跟踪]
        define26 --> define264[需求状态跟踪]

        devel --> devel1[业务流程设计]
        devel --> devel2[系统设计]
        devel --> devel3[编码]
        devel --> devel4[调试]
        devel --> devel5[测试]

        devel1 --> devel11[业务流程设计图]
        devel1 --> devel12[业务流程设计分类]

        devel2 --> devel21[系统设计目的]
        devel2 --> devel22[系统设计方法]
        devel2 --> devel23[系统设计内容]
        devel2 --> devel24[系统设计原则]
        devel2 --> devel25[衡量模块独立性的标准]
        devel2 --> devel26[人机设计三大黄金原则]

        devel25 --> devel251[内聚]
        devel25 --> devel252[耦合]

        devel5 --> devel51[测试原则]
        devel5 --> devel52[测试方法]
        devel5 --> devel53[测试阶段]

        run --> run1[遗留系统]
        run --> run2[系统转换]
        run --> run3[评价指标]
        run --> run4[维护类型]

        style lifecycle fill:#f9f,stroke:#333,stroke-width:2px
        style define fill:#bbf,stroke:#333
        style devel fill:#bbf,stroke:#333
        style run fill:#bbf,stroke:#333


.. _fig-Reverse-engineering:

.. mermaid::
   :caption: 逆向工程

    flowchart LR
        Reverse(逆向工程) ==> Levels([四个级别])
        Reverse ==> Other([其他概念])

        Levels --> Levels1[实现级]
        Levels --> Levels2[结构级]
        Levels --> Levels3[功能级]
        Levels --> Levels4[领域级]

        Other --> Other1[软件复用]
        Other --> Other2[重构]
        Other --> Other3[设计恢复]
        Other --> Other4[再工程]

        style Reverse fill:#f9f,stroke:#333,stroke-width:2px
