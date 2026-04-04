=============================
Information Security 信息安全
=============================

思维导图概览
------------

- :ref:`fig-Information-Security-Summary`


信息安全概述
------------

.. _fig-Information-Security-Summary:

.. mermaid::
   :caption: 信息安全概述

    flowchart LR
        Security(信息安全) ==> Essence([核心要素])
        Security ==> Layer([系统安全防范体系层次])
        Security ==> Range([安全范围])
        Security ==> Frame([信息安全系统组成框架])

        Essence --> Essence1[机密性]
        Essence --> Essence2[完整性]
        Essence --> Essence3[可用性]
        Essence --> Essence4[可控性]
        Essence --> Essence5[可审查性]

        Layer --> Layer1[安全管理]
        Layer --> Layer2[应用层安全]
        Layer --> Layer3[网络层安全]
        Layer --> Layer4[系统安全]
        Layer --> Layer5[物理层安全]

        Range --> Range1[设备安全]
        Range --> Range2[数据安全]
        Range --> Range3[内容安全]
        Range --> Range4[行为安全]

        Frame --> FrameTechnology[技术体系]
        Frame --> FrameOrganization[组织体系]
        Frame --> FrameManage[管理体系]

        FrameTechnology --> FT1[基础安全设备：U盾等]
        FrameTechnology --> FT2[计算机网络安全]
        FrameTechnology --> FT3[操作系统安全]
        FrameTechnology --> FT4[数据库安全]
        FrameTechnology --> FT5[终端安全设备]

        style Security fill:#f9f,stroke:#333,stroke-width:2px
