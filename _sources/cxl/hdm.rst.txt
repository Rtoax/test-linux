CXL HDM - Host-Managed Device
=============================

HDM Decoders are responsible for translating incoming Host Physical Addresses (HPA) into corresponding Device Physical Addresses (DPA), allowing memory accesses to be correctly directed to the appropriate device.

HDM decoders are mandatory for:

- CXL logical devices
- CXL type3 devices that are not RCDs
- CXL upstream switch ports
- CXL host bridge registers in CHBCR

System software can configure HDM decoders to control how memory is interleaved across CXL.mem-capable devices, enabling flexible and efficient memory mapping.

If no HDM decoders are programmed, CXL devices will fall back to using the CXL DVSEC range registers, which should be configured with the appropriate DPA range to ensure proper memory access.


Links
-----

- Demystifying CXL Memory Interleaving and HDM Decoder Configuration https://community.cadence.com/cadence_blogs_8/b/fv/posts/demystifying-cxl-memory-interleaving-and-hdm-decoder-configuration
