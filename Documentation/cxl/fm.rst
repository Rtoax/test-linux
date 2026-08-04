FM - Fabric Manager
===================

The **Fabric Manager** is an entity separate from the Switch or Host firmware that controls aspects of the system related to binding and management of pooled ports and devices.

CXL devices can be configured statically or dynamically via a Fabric Manager (FM), an external logical process that queries and configures the system’s operational state using the FM commands defined in this specification. The FM is defined as the logical process that decides when reconfiguration is necessary and initiates the commands to perform configurations. It can take any form, including, but not limited to, `software running on a host machine`, `embedded software running on a BMC`, `embedded firmware running on another CXL device or CXL switch`, or `a state machine running within the CXL device itself`.
