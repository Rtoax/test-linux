Memory
======

- SDRAM
- SRAM
- SRAM
- Cache


# DDR - Doubld Data Rate

- DDR3
  - maximum of 16GB memory
  - has lower latency than DDR4
  - has slower latency than DDR4
- DDR4
  - unlimited capability
  - has higher latency than DDR3
  - has faster latency than DDR4


# Memory Models

- **Sequential Consistency Models**
- **Nonsequential Consistency Models**
	- RAR: Read After Read
	- RAW: Read After Write
	- WAW: Write After Write
	- WAR: Write After Read

- `✔`: 表示不受影响
- `✗`: 表示受影响

| Type  |  x86   |  arm  |
| ----- | ------ | ----- |
|  RAW  |   ✗    |   ✗   |
|  WAW  |   ✔    |   ✗   |
|  WAR  |   ✔    |   ✗   |
|  RAR  |   ✔    |   ✗   |

