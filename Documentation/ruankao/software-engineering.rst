=============================
Software Engineering 软件工程
=============================

思维导图概览
------------

- :ref:`fig-Software-Engineering`
- :ref:`fig-Software-process-model`
- :ref:`fig-software-lifecycle`
- :ref:`fig-Reverse-engineering`
- :ref:`fig-Performance-Evaluation`
- :ref:`fig-DFD`
- :ref:`fig-DD`


软件工程概述
------------

.. _fig-Software-Engineering:

.. mermaid::
   :caption: 软件工程概述

    flowchart LR
        Engineering(软件工程概述) ==> Concept([基本概念])
        Engineering ==> PDCA([软件工程过程 PDCA])
        Engineering ==> Activity([四个活动])
        Engineering ==> Maturity([软件成熟度模型])

        Concept --> Concept1[定义]
        Concept --> Concept2[软件工程活动]
        Concept --> Concept3[软件工具分类]

        PDCA --> Plan[Plan 软件规格说明]
        PDCA --> Do[Do 软件开发]
        PDCA --> Check[Check 软件确认]
        PDCA --> Action[Action 软件演进]

        Activity --> Activity1[数据设计]
        Activity --> Activity2[架构/体系结构设计]
        Activity --> Activity3[人机界面/接口设计]
        Activity --> Activity4[过程/功能设计]

        Maturity --> CMM[CMM: 能力成熟度模型]
        Maturity --> Maturity2[CMMI: 能力成熟度模型集成]

        CMM --> CMM1[初始级] --> CMM1x[英雄]
        CMM --> CMM2[可重复级] --> CMM2x[过程准则、可重复]
        CMM --> CMM3[可定义级] --> CMM3x[文档化、标准化]
        CMM --> CMM4[已管理级] --> CMM4x[制定度量标准]
        CMM --> CMM5[优化级] --> CMM5x[持续改进]

        style Engineering fill:#f9f,stroke:#333,stroke-width:2px


软件过程模型
------------

.. _fig-Software-process-model:

.. mermaid::
   :caption: 软件过程模型

    flowchart LR
        Process(软件过程模型) ==> Traditional([传统模型])
        Process ==> Agile([敏捷模型])
        Process ==> Other([其他模型])

        Traditional --> WaterfallModel[瀑布模型]
        Traditional --> PrototypingModel[原型化模型]
        Traditional --> SpiralModel[螺旋模型]
        Traditional --> VModel[V 模型]
        Traditional --> WModel[W 模型]
        Traditional --> HModel[H 模型]

        WaterfallModel --> WaterfallModel1[风险控制力弱]
        WaterfallModel --> WaterfallModel2[每阶段文档]
        WaterfallModel --> WaterfallModel3[适用于需求明确]

        PrototypingModel --> PrototypingModel1[适用于需求不明确]

        SpiralModel --> SpiralModel1[强调风险]
        SpiralModel --> SpiralModel2[适用于庞大复杂高风险系统]

        VModel --> VModel1[需求分析] <--> VModel1x[验收测试]
        VModel --> VModel2[概要设计] <--> VModel2x[系统测试]
        VModel --> VModel3[详细设计] <--> VModel3x[集成测试]
        VModel --> VModel4[软件编码] <--> VModel4x[单元测试]

        Agile --> Agile1[核心思想] --> Agile11[以人为本、适应性]
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

        Agile5 --> Agile51[极限编程XP] --> Agile511[交流、朴素、反馈、勇气，见4大价值观]
        Agile5 --> Agile52[水晶系列方法] --> Agile521[以人为本，每个人都独特]
        Agile5 --> Agile53[并列争球法Scrum] --> Agile531[冲刺 Sprint，商业价值]
        Agile5 --> Agile54[特性驱动开发方法FDD] --> Agile541[迭代，人、过程、技术]

        Other --> IncrementalModel[增量模型] --> IncrementalModel1[每次增量版本都可独立发布]
        Other --> FountainModel[喷泉模型] --> FountainModel1[面向对象]
        Other --> RUP[RUP 统一过程模型]
        Other --> Cleanroom[净室软件工程]
        Other --> CBSE[基于构件的软件工程CBSE] --> CBSE1[快速开发模型，如低代码平台]

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
        RUP2 --> RUP22[细化阶段]
        RUP2 --> RUP23[构造阶段]
        RUP2 --> RUP24[移交阶段]

        RUP3 --> RUP31[用例驱动]
        RUP3 --> RUP32[以体系结构为中心]
        RUP3 --> RUP33[迭代与增量]

        RUP4 --> RUP41[用例视图] <--> RUP41x[测试人员、分析人员]
        RUP4 --> RUP42[逻辑视图] <--> RUP42x[用户]
        RUP4 --> RUP43[进程视图] <--> RUP43x[系统集成人员]
        RUP4 --> RUP44[实现试图] <--> RUP44x[开发人员、程序员]
        RUP4 --> RUP45[部署视图] <--> RUP45x[系统工程师]

        style Process fill:#f9f,stroke:#333,stroke-width:2px


软件生命周期
------------

.. _fig-software-lifecycle:

.. mermaid::
   :caption: 软件生命周期

    flowchart LR
        lifecycle(软件生命周期) ==> define([软件定义时期])
        lifecycle ==> devel([软件开发时期])
        lifecycle ==> run([软件运行维护时期])

        define --> define1[可行性研究]
        define --> ReqsEngineering[需求工程]

        ReqsEngineering --> ReqsClassification[需求分类]
        ReqsEngineering --> ReqsGathering[需求获取]
        ReqsEngineering --> ReqsAnalysis[需求分析]
        ReqsEngineering --> ReqsDefinition[需求定义SRS]
        ReqsEngineering --> ReqsVerification[需求验证/需求确认]
        ReqsEngineering --> ReqsManage[需求管理]

        ReqsClassification --> ReqsClassification1[业务需求]
        ReqsClassification --> ReqsClassification2[用户需求]
        ReqsClassification --> ReqsClassification3[系统需求]

        ReqsGathering --> ReqsGathering1[用户访谈] <--> ReqsGathering11[结构化、非结构化]
        ReqsGathering --> ReqsGathering2[问卷调查] <--> ReqsGathering21[杂乱]
        ReqsGathering --> ReqsGathering3[水平采样] <--> ReqsGathering31[数理统计]
        ReqsGathering --> ReqsGathering4[情节串联版] <--> ReqsGathering41[生动演示，耗时]
        ReqsGathering --> ReqsGathering5[联合需求计划 JRP] <--> ReqsGathering51[开会]
        ReqsGathering --> ReqsGathering6[需求记录技术]

        ReqsAnalysis --> ReqsAnalysis1[目的]
        ReqsAnalysis --> ReqsAnalysis2[步骤]
        ReqsAnalysis --> ReqsAnalysisMethod[方法]

        ReqsAnalysisMethod --> StructuredMethod[结构化方法]
        ReqsAnalysisMethod --> ReqsAnalysisMethod2[面向对象分析方法]

        StructuredMethod --> StructuredMethod1[特点]
        StructuredMethod --> StructuredMethod2[三大模型]
        StructuredMethod --> StructuredMethod3[数据流图DFD]

        StructuredMethod1 --> StructuredMethod11[自顶向下]
        StructuredMethod1 --> StructuredMethod12[逐步分解]
        StructuredMethod1 --> StructuredMethod13[面向数据]

        StructuredMethod2 --> StructuredMethod21[功能模型] <--> StructuredMethod21x[数据流图 DFD]
        StructuredMethod2 --> StructuredMethod22[行为模型] <--> StructuredMethod22x[状态转换图 STD]
        StructuredMethod2 --> StructuredMethod23[数据模型] <--> StructuredMethod23x[E-R 图]
        StructuredMethod2 --> StructuredMethod24[数据字典 DD]

        ReqsDefinition --> SRS[软件需求规格说明书]
        ReqsDefinition --> ReqsDefinitionMethod[需求定义方法]

        ReqsDefinitionMethod --> ReqsDefinitionMethod1[严格定义、预先定义，结构化定义]
        ReqsDefinitionMethod --> ReqsDefinitionMethod2[原型方法]

        ReqsVerification --> ReqsVerificationProcedure[步骤]

        ReqsVerificationProcedure --> ReqsVerificationProcedure1[需求评审]
        ReqsVerificationProcedure --> ReqsVerificationProcedure2[需求测试]

        ReqsManage --> ReqsManage1[变更控制]
        ReqsManage --> ReqsManage2[版本控制]
        ReqsManage --> ReqsManage3[需求跟踪]
        ReqsManage --> ReqsManage4[需求状态跟踪]

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


数据流图 DFD
------------

.. _fig-DFD:

.. mermaid::
   :caption: 数据流图 DFD

    flowchart LR
        DFD(数据流图) ==> DataFlow([数据流]) <--> DD-DataFlow[数据字典DD：数据流]
        DFD ==> DataStore([数据存储]) <--> DD-DataStore[数据字典DD：数据存储]
        DFD ==> Process([加工]) <--> DD-ProcessLogic[数据字典DD：加工逻辑]
        DFD ==> Entity([外部实体]) <--> DD-Entity[数据字典DD：外部实体]


数据字典 DD
-----------

.. _fig-DD:

.. mermaid::
   :caption: 数据字典 DD

    flowchart LR
        DD(数据字典) ==> DataElement([数据元素])
        DD ==> DataStructure([数据结构])
        DD ==> DataFlow([数据流]) <--> DFD-DataFlow[DFD:数据流]
        DD ==> DataStore([数据存储]) <--> DFD-DataStore[DFD:数据存储]
        DD ==> ProcessLogic([加工逻辑]) <--> DFD-Process[DFD:加工]
        DD ==> Entity([外部实体]) <--> DFD-Entity[DFD:外部实体]


逆向工程
--------

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


性能评价
--------

.. _fig-Performance-Evaluation:

.. mermaid::
   :caption: 性能评价

    flowchart LR
        Perf(性能评价) ==> Indicator([性能指标])
        Perf ==> Method([性能评价方法])
        Perf ==> Amdahl([阿姆达尔定律])

        style Perf fill:#f9f,stroke:#333,stroke-width:2px
