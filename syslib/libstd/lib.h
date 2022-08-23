/*	* lib.h
	* The assembly lib link lin header of OS
	* Current OS Version 0.02PreChannel3
	* finished at 2022/8/18
	* Author: Sino Kiwi,ZZC
	* Copyright (c) 2022 SinoKiwi
*/

#ifndef __LIB_H__
#define __LIB_H__

#define sti() 		__asm__ __volatile__ ("sti	\n\t":::"memory")
#define cli()	 	__asm__ __volatile__ ("cli	\n\t":::"memory")
#define nop() 		__asm__ __volatile__ ("nop	\n\t")
#define io_mfence() 	__asm__ __volatile__ ("mfence	\n\t":::"memory")
#define barrier()	__asm__ __volatile__ ("":::"memory")

#define hlt() 		__asm__ __volatile__ ("hlt	\n\t")
#define pause() 	__asm__ __volatile__ ("pause	\n\t")

#define port_insw(port,buffer,nr)	\
__asm__ __volatile__("cld;rep;insw;mfence;"::"d"(port),"D"(buffer),"c"(nr):"memory")

#define port_outsw(port,buffer,nr)	\
__asm__ __volatile__("cld;rep;outsw;mfence;"::"d"(port),"S"(buffer),"c"(nr):"memory")

inline void* memcpy(void* From, void* To, long Num);
inline int memcmp(void* FirstPart, void* SecondPart, long Count);
inline void* memset(void* Address, unsigned char C, long Count);
inline char* strcpy(char* Dest, char* Src);
inline char* strncpy(char* Dest, char* Src, long Count);
inline char* strcat(char* Dest, char* Src);
inline int strcmp(char* FirstPart, char* SecondPart);
inline int strncmp(char* FirstPart, char* SecondPart, long Count);
inline int strlen(char* String);

inline unsigned char io_in8(unsigned short port);
inline unsigned int io_in32(unsigned short port);
inline void io_out8(unsigned short port, unsigned char value);
inline void io_out32(unsigned short port, unsigned int value);

inline unsigned long rdmsr(unsigned long address);
inline void wrmsr(unsigned long address, unsigned long value);

inline unsigned long get_rsp();
inline unsigned long get_rflags();

#endif