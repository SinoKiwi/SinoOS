/*	*  EFI_BOOT_INFO.h
	*  UEFI Bootloader used to pass the system hardware info to kernel,
  	*  Current OS Version 0.02PreChannel3 ,LoaderVer 0.3
  	*  finished at 2022/8/23
  	*  Done:Pass ACPI Table to kernel
  	*  Author: Sino Kiwi,ZZC
  	*  Copyright (c) 2022 SinoKiwi
*/

#ifndef __EFI_BOOT_INFO_H__
#define __EFI_BOOT_INFO_H__

#define WRITE_DONE_FLAG 829340
#define NOT_WRITE_DONE 203947
#define UNKNOWN_WRITED_STATUS 0

struct ACPI_TABLES_INFO{
	int if_acpi_right_version_exist;
	int * rsdp_addr;
};

struct EFI_BOOT_HW_INFO{
	int ifwritedone;
	int checkwritedone;
	struct ACPI_TABLES_INFO acpi_table_info;
} efi_boot_hardware_info;

#endif
