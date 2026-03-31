============================
System Architecture Designer
============================

思维导图
--------

- :ref:`fig-software-lifecycle`


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
