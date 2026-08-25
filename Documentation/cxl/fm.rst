FM API - Fabric Manager Application Programming Interface
=========================================================

The **Fabric Manager** is an entity separate from the Switch or Host firmware that controls aspects of the system related to binding and management of pooled ports and devices.

CXL devices can be configured statically or dynamically via a Fabric Manager (FM), an external logical process that queries and configures the system’s operational state using the FM commands defined in this specification. The FM is defined as the logical process that decides when reconfiguration is necessary and initiates the commands to perform configurations. It can take any form, including, but not limited to:

- software running on a host machine;
- embedded software running on a `BMC`;
- embedded firmware running on another CXL device or CXL switch;
- a state machine running within the CXL device itself;


Links
-----

Specifications
~~~~~~~~~~~~~~

- CXL Consortium, Compute Express Link™ (CXL™) Specification Revision 2.0: https://www.computeexpresslink.org
- CXL™ Fabric Manager API over MCTP Binding Specification: https://www.dmtf.org/sites/default/files/standards/documents/DSP0234_1.0.0.pdf
- DMTF DSP0236, Management Component Transport Protocol (MCTP) Base Specification 1.3: https://www.dmtf.org/sites/default/files/standards/documents/DSP0236_1.3.pdf
        - MCTP Specification DSP0236: https://www.dmtf.org/dsp/DSP0236
- DMTF DSP0237, Management Component Transport Protocol (MCTP) SMBus/I2C Transport Binding Specification 1.2: https://www.dmtf.org/sites/default/files/standards/documents/DSP0237_1.2.pdf
- DMTF DSP0238, Management Component Transport Protocol (MCTP) PCIe VDM Transport Binding Specification 1.1: https://www.dmtf.org/sites/default/files/standards/documents/DSP0238_1.1.pdf
- DMTF DSP0239, Management Component Transport Protocol (MCTP) IDs and Codes 1.7: https://www.dmtf.org/sites/default/files/standards/documents/DSP0239_1.7.pdf

Codes
~~~~~

- https://github.com/computexpresslink/libcxlmi.git
