#pragma once

/**
 * https://developer.arm.com/documentation/ddi0595/2021-12/External-Registers/MIDR-EL1--Main-ID-Register
 */
#define ARM		0x41
#define Broadcom	0x42
#define Cavium		0x43
#define DigitalEquipment	0x44
#define Fujitsu		0x46
#define HiSilicon	0x48
#define Infineon	0x49
#define Freescale	0x4D
#define NVIDIA		0x4E
#define APM		0x50
#define Qualcomm	0x51
#define Marvell		0x56
#define Intel		0x69
#define Ampere		0xC0


int get_cpuid(unsigned long *flags);

