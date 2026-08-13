=======
Storage
=======

.. toctree::
   :maxdepth: 1

   abbrev
   abbrev-nvme


Technology
----------

.. toctree::
   :maxdepth: 1

   block
   bio
   ceph
   dax
   device-mapper
   eMMC
   flash
   iscsi
   io-sched/index
   jbod
   lvm
   multipath
   nbd
   ndctl
   nvdimm
   nvme
   pmem
   raid
   raid-software
   scsi
   spdk
   vmem


Tools
-----

.. toctree::
   :maxdepth: 1

   libblockdev


主流的软件分区技术
------------------

- `MBR`: Master Boot Record
	- 支持最大`2TB`硬盘
	- 正在被`GPT`取代
- `GPT`: GUID Partition Table
	- 支持最大`128PB`(1PB=1024TB)


Links
-----

- GitHub: https://github.com/storaged-project/
    - GitHub blivet: https://github.com/storaged-project/blivet.git
- https://www.thomas-krenn.com/en/wiki/Linux_I/O_Stack_Diagram
