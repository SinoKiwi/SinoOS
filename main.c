/*	* main.c
	* The Main Part Of OS Kernel
	* Current OS Version 0.02PreChannel3,KV(Kernel Version)0
	* finished at 2022/8/18
	* Done:Start Process;:Clear screen(fill the screen with black)
	* Compiled by gcc,linked with khead_desc.S by ld
	* Author: Sino Kiwi,ZZC
	* Copyright (c) 2022 SinoKiwi
*/
#include "syslib/subkernellib/graphic.h"
#include "syslib/syslib/acpi.h"
#include "syslib/syslib/EFI_BOOT_INFO.h"

void KMain(void) {
	/*int* addr = (int*)0xffff800003000000;
	int i;
	for (i = 0; i < 2048 * 900; i++)
	{
		*((char*)addr + 0) = (char)0x00;//ff
		*((char*)addr + 1) = (char)0x00;//ff
		*((char*)addr + 2) = (char)0x00;//ff
		*((char*)addr + 3) = (char)0x00;
		addr += 1;
	}	//clear screen*/

	//check boot param
	if (efi_boot_hardware_info.ifwritedone = 1) {
		if(efi_boot_hardware_info.checkwritedone != WRITE_DONE_FLAG) {
			while(1);
		}
	} else {
		while(1);
	}
	
	acpi_init();

	screen_firstinit();

	while (1);

}