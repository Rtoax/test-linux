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

        Model --> ER[E-R 模型]
        Model --> Model2[关系模型]
        Model --> ModelElement[模型三要素]

        ER --> ER1[实体]
        ER --> ER2[属性]
        ER --> ER3[联系]

        ER1 --> ER11[强实体，弱实体]
        ER3 --> ER31[1对1，1对多，多对1]

        ModelElement --> ModelElement1[数据结构]
        ModelElement --> ModelElement2[数据操作]
        ModelElement --> ModelElement3[数据的约束条件]

        RelationalAlgebra --> RelationalAlgebra1[集合运算符]
        RelationalAlgebra --> RelationalAlgebra2[关系运算符]
        RelationalAlgebra --> RelationalAlgebra3[比较运算符]
        RelationalAlgebra --> RelationalAlgebra4[逻辑运算符]

        RelationalAlgebra1 --> RelationalAlgebra11[并，交∩，差，笛卡尔积]
        RelationalAlgebra2 --> RelationalAlgebra21[选择，投影，连接，除]
        RelationalAlgebra3 --> RelationalAlgebra31[大于，小于，...]
        RelationalAlgebra4 --> RelationalAlgebra41[与，或，非]

        Norm --> FunctionDependency[函数依赖]
        Norm --> KeysConstraints[键与约束]
        Norm --> NormalForms[范式]
        Norm --> ModeDecomposition[模式分解]
        Norm --> Denormalization[反规范化]
        Norm --> NonNormalizationProblems[不规范化带来的问题]

        FunctionDependency --> FunctionDependency1[部分函数依赖]
        FunctionDependency --> FunctionDependency2[传递函数依赖]
        FunctionDependency --> Armstrong([阿姆斯特朗公理])

        NormalForms --> 1NF[第一范式 1NF] --> 1NFx[属性不可分割]
        NormalForms --> 2NF[第一范式 2NF] --> 2NFx[不能存在联合主键]
        NormalForms --> 3NF[第一范式 3NF] --> 3NFx[不能存在传递依赖]
        NormalForms --> BCNF[BC范式 BCNF] --> BCNFx[3NF+避免数据冗余和不一致性]

        ModeDecomposition --> MD1[是否保持函数依赖]
        ModeDecomposition --> MD2[有损无损分解] --> MD2x[无损的充要条件: R1∩R1 -> R1-R2]

        Denormalization --> DNx([牺牲部分规范化提高性能])
        Denormalization --> DN1[增加冗余列]
        Denormalization --> DN2[增加派生列]
        Denormalization --> DN3[重新组表]
        Denormalization --> DN4[水平分割表]
        Denormalization --> DN5[垂直分割表]

        NonNormalizationProblems --> NNP1[数据冗余]
        NonNormalizationProblems --> NNP2[修改异常]
        NonNormalizationProblems --> NNP3[插入异常]
        NonNormalizationProblems --> NNP4[删除异常]

        Armstrong --> Armstrong1[自反律]
        Armstrong --> Armstrong2[增广律]
        Armstrong --> Armstrong3[传递律]
        Armstrong --> Armstrong4[合并律]
        Armstrong --> Armstrong5[分解律]
        Armstrong --> Armstrong6[合成律]

        KeysConstraints --> Keys[键]

        Keys --> Key1[超键] --> Key11[唯一标识一条记录的属性/属性集]
        Keys --> Key2[候选键] --> Key21[无冗余属性的超键]
        Keys --> Key3[主属性] --> Key31[候选键中的属性]
        Keys --> Key4[主键] --> Key41[候选键中的一个属性/属性集]
        Keys --> Key5[外键] --> Key51[建立表之间的关系]

        Control --> Transaction[事物] --> ACID[ACID]
        Control --> Concurrency[并发控制]
        Control --> Blockade[封锁协议]

        Concurrency --> ConcurrencyProblem[三种安全问题]

        ConcurrencyProblem --> ConcurrencyProblem1[丢失更新]
        ConcurrencyProblem --> ConcurrencyProblem2[不可重复读]
        ConcurrencyProblem --> ConcurrencyProblem3[读脏数据]

        Blockade --> LockX([X锁是排他锁/写锁🔓])
        Blockade --> LockS([S锁是共享锁/读锁🔓])
        Blockade --> 1Blockade[一级封锁协议] --> 1Bx[修改前必须加X写锁]
        Blockade --> 2Blockade[二级封锁协议] --> 2Bx[一级封锁协议 + 读之前必须加S读锁]
        Blockade --> 3Blockade[三级封锁协议] --> 3Bx[一级封锁协议 + 事物T在读前加S读锁]

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
