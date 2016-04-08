/*
 * Copyright (c) 2006-2007 -  http://brynet.biz.tm - <brynet@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* You need to include a file with fairly(ish) compliant kprint prototype, Decimal and String support like %s and %d and this is truely all you need! */
//#include <stdio.h> /* for kprint(); */
#include "../sys/system.h"
#include "cpuid.h"

/* Required Declarations */
int do_intel(void);
int do_amd(void);
void printregs(int eax, int ebx, int ecx, int edx);

#define cpuid(in, a, b, c, d) __asm__("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));

/* Simply call this function detect_cpu(); */
int detect_cpu() { /* or main() if your trying to port this as an independant application */
	unsigned long ebx, unused;
	cpuid(0, unused, ebx, unused, unused);
	switch(ebx) {
		case 0x756e6547: /* Intel Magic Code */
		do_intel();
		break;
		case 0x68747541: /* AMD Magic Code */
		do_amd();
		break;
		default:
		kprint("Unknown x86 CPU Detected\n");
		break;
	}
	return 0;
}

/* Intel Specific brand list */
char *Intel[] = {
	"Brand ID Not Supported.", 
	"Intel(R) Celeron(R) processor", 
	"Intel(R) Pentium(R) III processor", 
	"Intel(R) Pentium(R) III Xeon(R) processor", 
	"Intel(R) Pentium(R) III processor", 
	"Reserved", 
	"Mobile Intel(R) Pentium(R) III processor-M", 
	"Mobile Intel(R) Celeron(R) processor", 
	"Intel(R) Pentium(R) 4 processor", 
	"Intel(R) Pentium(R) 4 processor", 
	"Intel(R) Celeron(R) processor", 
	"Intel(R) Xeon(R) Processor", 
	"Intel(R) Xeon(R) processor MP", 
	"Reserved", 
	"Mobile Intel(R) Pentium(R) 4 processor-M", 
	"Mobile Intel(R) Pentium(R) Celeron(R) processor", 
	"Reserved", 
	"Mobile Genuine Intel(R) processor", 
	"Intel(R) Celeron(R) M processor", 
	"Mobile Intel(R) Celeron(R) processor", 
	"Intel(R) Celeron(R) processor", 
	"Mobile Geniune Intel(R) processor", 
	"Intel(R) Pentium(R) M processor", 
	"Mobile Intel(R) Celeron(R) processor"
};

/* This table is for those brand strings that have two values depending on the processor signature. It should have the same number of entries as the above table. */
char *Intel_Other[] = {
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Celeron(R) processor", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Xeon(R) processor MP", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Xeon(R) processor", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved"
};

/* Intel-specific information */
int do_intel(void) {
	kprint("Intel Specific Features:\n");
	unsigned long eax, ebx, ecx, edx, max_eax, signature, unused;
	int model, family, type, brand, stepping, reserved;
	int extended_family = -1;
	cpuid(1, eax, ebx, unused, unused);
	model = (eax >> 4) & 0xf;
	family = (eax >> 8) & 0xf;
	type = (eax >> 12) & 0x3;
	brand = ebx & 0xff;
	stepping = eax & 0xf;
	reserved = eax >> 14;
	signature = eax;
	kprint("Type ");kpi(type);kps(" - ");
	switch(type) {
		case 0:
		kprint("Original OEM");
		break;
		case 1:
		kprint("Overdrive");
		break;
		case 2:
		kprint("Dual-capable");
		break;
		case 3:
		kprint("Reserved");
		break;
	}
	kprint("\n");
	kprint("Family ");kpi(family);kps(" - ");
	switch(family) {
		case 3:
		kprint("i386");
		break;
		case 4:
		kprint("i486");
		break;
		case 5:
		kprint("Pentium");
		break;
		case 6:
		kprint("Pentium Pro");
		break;
		case 15:
		kprint("Pentium 4");
	}
	kprint("\n");
	if(family == 15) {
		extended_family = (eax >> 20) & 0xff;
		kprint("Extended family ");kpi(extended_family);kps("\n");
	}
	kprint("Model ");kpi(model);kps(" - ");
	switch(family) {
		case 3:
		break;
		case 4:
		switch(model) {
			case 0:
			case 1:
			kprint("DX");
			break;
			case 2:
			kprint("SX");
			break;
			case 3:
			kprint("487/DX2");
			break;
			case 4:
			kprint("SL");
			break;
			case 5:
			kprint("SX2");
			break;
			case 7:
			kprint("Write-back enhanced DX2");
			break;
			case 8:
			kprint("DX4");
			break;
		}
		break;
		case 5:
		switch(model) {
			case 1:
			kprint("60/66");
			break;
			case 2:
			kprint("75-200");
			break;
			case 3:
			kprint("for 486 system");
			break;
			case 4:
			kprint("MMX");
			break;
		}
		break;
		case 6:
		switch(model) {
			case 1:
			kprint("Pentium Pro");
			break;
			case 3:
			kprint("Pentium II Model 3");
			break;
			case 5:
			kprint("Pentium II Model 5/Xeon/Celeron");
			break;
			case 6:
			kprint("Celeron");
			break;
			case 7:
			kprint("Pentium III/Pentium III Xeon - external L2 cache");
			break;
			case 8:
			kprint("Pentium III/Pentium III Xeon - internal L2 cache");
			break;
		}
		break;
		case 15:
		break;
	}
	kprint("\n");
	cpuid(0x80000000, max_eax, unused, unused, unused);
	/* Quok said: If the max extended eax value is high enough to support the processor brand string
	(values 0x80000002 to 0x80000004), then we'll use that information to return the brand information. 
	Otherwise, we'll refer back to the brand tables above for backwards compatibility with older processors. 
	According to the Sept. 2006 Intel Arch Software Developer's Guide, if extended eax values are supported, 
	then all 3 values for the processor brand string are supported, but we'll test just to make sure and be safe. */
	if(max_eax >= 0x80000004) {
		kprint("Brand: ");
		if(max_eax >= 0x80000002) {
			cpuid(0x80000002, eax, ebx, ecx, edx);
			printregs(eax, ebx, ecx, edx);
		}
		if(max_eax >= 0x80000003) {
			cpuid(0x80000003, eax, ebx, ecx, edx);
			printregs(eax, ebx, ecx, edx);
		}
		if(max_eax >= 0x80000004) {
			cpuid(0x80000004, eax, ebx, ecx, edx);
			printregs(eax, ebx, ecx, edx);
		}
		kprint("\n");
	} else if(brand > 0) {
		kprint("Brand ");kpi(brand);kps(" - ");
		if(brand < 0x18) {
			if(signature == 0x000006B1 || signature == 0x00000F13) {
				kprint(Intel_Other[brand]);kps("\n");
			} else {
				kprint(Intel[brand]);kps("\n");
			}
		} else {
			kprint("Reserved\n");
		}
	}
	kprint("Stepping: ");kpi(stepping);kps(" Reserved: ");kpi(reserved);kps("\n");
	return 0;
}

/* Print Registers */
void printregs(int eax, int ebx, int ecx, int edx) {
	int j;
	char string[17];
	string[16] = '\0';
	for(j = 0; j < 4; j++) {
		string[j] = eax >> (8 * j);
		string[j + 4] = ebx >> (8 * j);
		string[j + 8] = ecx >> (8 * j);
		string[j + 12] = edx >> (8 * j);
	}
	kprint(string);
}

/* AMD-specific information */
int do_amd(void) {
	kprint("AMD Specific Features:\n");
	unsigned long extended, eax, ebx, ecx, edx, unused;
	int family, model, stepping, reserved;
	cpuid(1, eax, unused, unused, unused);
	model = (eax >> 4) & 0xf;
	family = (eax >> 8) & 0xf;
	stepping = eax & 0xf;
	reserved = eax >> 12;
	kprint("Family: ");kpi(family);kps(" Model: ");kpi(model);kps(" [");
	switch(family) {
		case 4:
		kprint("486 Model ");kpi(model);
		break;
		case 5:
		switch(model) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 6:
			case 7:
			kprint("K6 Model ");kpi(model);
			break;
			case 8:
			kprint("K6-2 Model 8");
			break;
			case 9:
			kprint("K6-III Model 9");
			break;
			default:
			kprint("K5/K6 Model ");kpi(model);
			break;
		}
		break;
		case 6:
		switch(model) {
			case 1:
			case 2:
			case 4:
			kprint("Athlon Model ");kpi(model);
			break;
			case 3:
			kprint("Duron Model 3");
			break;
			case 6:
			kprint("Athlon MP/Mobile Athlon Model 6");
			break;
			case 7:
			kprint("Mobile Duron Model 7");
			break;
			default:
			kprint("Duron/Athlon Model ");kpi(model);
			break;
		}
		break;
	}
	kprint("]\n");
	cpuid(0x80000000, extended, unused, unused, unused);
	if(extended == 0) {
		return 0;
	}
	if(extended >= 0x80000002) {
		unsigned int j;
		kprint("Detected Processor Name: ");
		for(j = 0x80000002; j <= 0x80000004; j++) {
			cpuid(j, eax, ebx, ecx, edx);
			printregs(eax, ebx, ecx, edx);
		}
		kprint("\n");
	}
	if(extended >= 0x80000007) {
		cpuid(0x80000007, unused, unused, unused, edx);
		if(edx & 1) {
			kprint("Temperature Sensing Diode Detected!\n");
		}
	}
	kprint("Stepping: ");kpi(stepping);kps(" Reserved: ");kpi(reserved);kps("\n");
	return 0;
}
