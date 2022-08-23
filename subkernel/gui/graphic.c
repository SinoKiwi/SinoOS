/*	* graphic.c
	* The graphic part of OS, GUI SubKernel
	* Current OS Version 0.02PreChannel3,KV(Kernel Version)0,SKV(Sub Kernel Version)0
	* finished at 2022/8/18
	* Done:Draw Fullscreen
	* Compiled by gcc
	* Author: Sino Kiwi,ZZC
	* Copyright (c) 2022 SinoKiwi
*/

#include "../../syslib/subkernellib/graphic.h"
#include "../../syslib/libstd/lib.h"

int* addrbase = (int*)0xffff800003000000;


void screen_firstinit() {
	screen_drawrectangle(gra_pixel2addr(300, 300, 2048, 2048), 300, 300, 20, 50, 5, 1600, 900);
}

void screen_drawrectangle(int* paddrstart, int pxlinest, int pxlistst, int w, int h, int color_num, int scanline, int vertical) {
	int* addrcache = paddrstart;
	int* addrcache1, addrcache2;
	int i = 0;
	int j = 0;
	int r, g, b;
	switch (color_num) //White:0,Black:1,Red:2,green:3,blue:4,orange:5,yellow:6,pink:7,cyan:8,deep blue:9,brown:10
	{
	case 0:
		r = WHITE_R;
		g = WHITE_G;
		b = WHITE_B;
		break;
	case 1:
		r = BLK_R;
		g = BLK_G;
		b = BLK_B;
		break;
	case 2:
		r = RED_R;
		g = RED_G;
		b = RED_B;
		break;
	case 3:
		r = GREEN_R;
		g = GREEN_G;
		b = GREEN_B;
		break;
	case 4:
		r = BLUE_R;
		g = BLUE_G;
		b = BLUE_B;
		break;
	case 5:
		r = ORG_R;
		g = ORG_G;
		b = ORG_B;
		break;
	case 6:
		r = YL_R;
		g = YL_G;
		b = YL_B;
		break;
	case 7:
		r = PINK_R;
		g = PINK_G;
		b = PINK_B;
		break;
	case 8:
		r = CYAN_R;
		g = CYAN_G;
		b = CYAN_B;
		break;
	case 9:
		r = DPBL_R;
		g = DPBL_G;
		b = DPBL_B;
		break;
	case 10:
		r = BROWN_R;
		g = BROWN_G;
		b = BROWN_B;
		break;
	default:
		return;
	}

		for (i = 0; i < h; i++)

		{
			addrcache1 = gra_pixel2addr(pxlinest + i, pxlistst, scanline, vertical);
			for (j = 0; j < w; j++) {

				*((char*)addrcache + 0) = (char)b;

				*((char*)addrcache + 1) = (char)g;

				*((char*)addrcache + 2) = (char)r;

				*((char*)addrcache + 3) = (char)0x00;

				addrcache += 1;
			}

		}

	}

int * gra_pixel2addr(int pxline, int pxlist,int scanline,int vertical) {//2048,2048 is qemu
	//int scanline = 2048;//get from UEFI Print
	//int vertical = 2048;//get from UEFI Print
	//mean rr(·Ö±æÂÊ) is 2048*2048(scanline*vertical)

	if (pxline > scanline || pxlist > vertical)
		return;
	if (pxline < 0 || pxlist < 0)
		return;
	//unknown pxline & pxlist

	int * addrcache;

	addrcache = 0 + (pxline + 1) * 11 + pxline * 1 - (scanline - pxlist);//pixel addr

	return addrcache;

}
