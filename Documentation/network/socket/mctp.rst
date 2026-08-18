MCTP - Management Component Transport Protocol
==============================================

MCTP 是一个管理组件传输协议，是一个用于管理控制器（BMC）和管理控制器之间及管理控制器和管理设备之间的通信协议。

BMC 可以用这个协议在多种不同的总线类型通过发送和接收MCTP格式的消息去访问管理设备。系统中的管理设备需要提供一个消息格式定义的实施方案方便管理控制器的相关操作。这就意味着在管理系统中不同类型的设备可能会提供不同的实现MCTP的具体方案。

MCTP可通过多种媒介发送，例如 **PCIe** 、 **SMBus/I2C** 、 **UART** 、 **Host Interface** 、 **USB** 等。

MCTP可以在公共传输层上传输多种类型的消息，例如 **NCSI** 、 **Ethernet** 、 **OEM defined** （原始制造商自定义）、 **PLDM** （Platform-Level Data model）。

一个系统可以包括多个MCTP网络，MCTP的网络包括多个physical transports，用于多个MCTP Endpoint之间的MCTP报文传输，MCTP Endpoint就是MCTP通信的一个终点。一个物理设备可以支持多个MCTP Endpoint，Endpoint的寻址是逻辑地址称为EID，EID类似于互联网上的IP地址。


MCTP protocol support
---------------------

.. list-table::
   :header-rows: 1

   * - Protocol
     - Can encapsulate(封装)
     - Can transmit over
   * - PCI Express
     - MI
     - VDM
   * - NVM Express
     - Management Messages
     - ❌
   * - CXL (Fabric Manager, Type 3 DCCI)
     - ✅
     - ❌
   * - Platform Level Data Model
     - ✅
     - ❌
   * - NC-SI, Ethernet
     - ✅
     - ❌
   * - USB
     - ❌
     - ✅
   * - I2C/SMBus, I3C (incl. PCIe)
     - ❌
     - ✅
   * - Serial Port
     - ❌
     - ✅
   * - ACPI PCC
     - ❌
     - ✅
   * - UCIe
     - ❌
     - ✅
   * - KCS
     - ❌
     - ✅
   * - MMBI (incl. PCIe)
     - ❌
     - ✅


Links
-----

Specifications
~~~~~~~~~~~~~~

- MCTP Specification DSP0236: https://www.dmtf.org/dsp/DSP0236
- Linux Kernel: https://docs.kernel.org/networking/mctp.html
- CXL Consortium, Compute Express Link™ (CXL™) Specification Revision 2.0: https://www.computeexpresslink.org
- DMTF DSP0256, MCTP over USB
- DMTF DSP0236, MCTP Base Specification 1.3: https://www.dmtf.org/sites/default/files/standards/documents/DSP0236_1.3.pdf
        - Newest `MCTP Specification <https://www.dmtf.org/dsp/DSP0236>`_ is `1.3.3 <https://www.dmtf.org/sites/default/files/standards/documents/DSP0236_1.3.3.pdf>`_.
- DMTF DSP0237, MCTP SMBus/I2C Transport Binding Specification 1.2: https://www.dmtf.org/sites/default/files/standards/documents/DSP0237_1.2.pdf
- DMTF DSP0238, MCTP PCIe VDM Transport Binding Specification 1.1: https://www.dmtf.org/sites/default/files/standards/documents/DSP0238_1.1.pdf
- DMTF DSP0239, MCTP IDs and Codes 1.7: https://www.dmtf.org/sites/default/files/standards/documents/DSP0239_1.7.pdf

Codes
~~~~~

- https://en.wikipedia.org/wiki/Management_Component_Transport_Protocol
- https://github.com/CodeConstruct/mctp
