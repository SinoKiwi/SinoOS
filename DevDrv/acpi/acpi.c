/*	* main.c
	* The acpi drive
	* Current OS Version 0.02PreChannel3
	* finished at 2022/8/18
	* Done:Get rsdp from uefi loader
	* Compiled by gcc
	* Author: Sino Kiwi,ZZC
	* Copyright (c) 2022 SinoKiwi
*/

int * rsdp_addr = efi_boot_hardware_info.acpi_table_info.rsdp_addr;

void acpi_init(){
}