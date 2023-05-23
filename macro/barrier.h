#pragma once

#define mb()	asm volatile("mfence":::"memory")

