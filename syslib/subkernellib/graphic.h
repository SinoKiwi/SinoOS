/*	* graphic.h
	* The graphic header part of OS, GUI SubKernel
	* Current OS Version 0.02PreChannel3,KV(Kernel Version)0,SKV(Sub Kernel Version)0
	* finished at 2022/8/18
	* Done:Draw Fullscreen
	* Compiled by gcc
	* Author: Sino Kiwi,ZZC
	* Copyright (c) 2022 SinoKiwi
*/

#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include "../../syslib/libstd/lib.h"


//white
#define WHITE_R 0xff
#define WHITE_G      0xff
#define WHITE_B 0xff

//black
#define BLK_R 0x00
#define BLK_G 0x00
#define BLK_B 0x00

//red
#define RED_R 0xff
#define RED_G 0x00
#define RED_B 0x00

//green
#define GREEN_R 0x00
#define GREEN_G 0xff
#define GREEN_B 0x00

//blue
#define BLUE_R 0x00
#define BLUE_G 0x00
#define BLUE_B 0xff

//orange
#define ORG_R 0xff
#define ORG_G 0xa5
#define ORG_B 0x00

//yellow
#define YL_R 0xff
#define YL_G 0xff
#define YL_B 0x00

//pink
#define PINK_R 0xff
#define PINK_G 0xc0
#define PINK_B 0xcb

//cyan
#define CYAN_R 0x00
#define CYAN_G 0xff
#define CYAN_B 0xff

//deep blue
#define DPBL_R 0x19
#define DPBL_G 0x19
#define DPBL_B 0x70

//brown802a2a
#define BROWN_R 0x80
#define BROWN_G 0x2a
#define BROWN_B 0x2a


void screen_firstinit();
void screen_drawrectangle(int* paddrstart, int pxlinest, int pxlistst, int w, int h, int color_num, int scanline, int vertical)；int * gra_pixel2addr(int pxline,int pxlist,int scanline,int vertical);
/*
*	see docs/screen.txt
*/

#endif