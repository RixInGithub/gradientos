/*
	╔════════════════════════════════════════════════════════════════════════════╗
	║ ╔══════╗  .   .   .   .   ╔═╗  ╔╗  .   .   .   .   ╔═╗   ╔══════╗ ╔══════╗ ║
	║ ║ ╔════╝  .   .   .   .   ║ ║  ╚╝  .   .   .   .  ╔╝ ╚╗  ║ ╔══╗ ║ ║ ╔════╝ ║
	║ ║ ║╔═══╗ ╔════╗ ╔════╗ ╔══╝ ║ ╔══╗  ╔════╗ ╔════╗ ╚╗ ╔╝  ║ ║  ║ ║ ║ ╚════╗ ║
	║ ║ ║╚═╗ ║ ║ ╔══╝ ╠═══ ║ ║ ╔╗ ║ ╚╗ ║  ║ ── ║ ║ ╔╗ ║  ║ ║   ║ ║  ║ ║ ╚════╗ ║ ║
	║ ║ ╚══╝ ║ ║ ║  . ║ ── ║ ║ ╚╝ ║  ║ ╚╗ ║ ═══╣ ║ ║║ ║  ║ ╚═╗ ║ ╚══╝ ║ ╔════╝ ║ ║
	║ ╚══════╝ ╚═╝  . ╚════╝ ╚════╝  ╚══╝ ╚════╝ ╚═╝╚═╝  ╚═══╝ ╚══════╝ ╚══════╝ ║
	╚════════════════════════════════════════════════════════════════════════════╝
	Ⓒ GradientOS 2024-present. All rights reserved. Hosted by Neocities.
*/
#include <stdio.h>
#include <emscripten.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

int width = 384;
int height = 216;
int scrArea;
int *screen;
int initCol = 0xf5a097;

void getXYFrom1D(int px, int *x, int *y) {
	*x = px % width;
	*y = (int)floor((double)px / width);
}

int get1DFromXY(int x, int y) {
	return y * width + x;
}

void EMSCRIPTEN_KEEPALIVE setPixel(int x, int y, int hex) {
	screen[get1DFromXY(x, y)] = hex;
}

void fillRectOnScr(int x, int y, int w, int h, int hex) { // ...since 2024/04/15
	if (x > width) return;
	if (y > height) return;
	// TODO: add more edge-cases here
	int xCnt;
	int yCnt = 0;
	while (yCnt < h) {
		xCnt = 0;
		while (xCnt < w) {
			setPixel(x + xCnt, y + yCnt, hex);
			xCnt += 1;
		}
		yCnt += 1;
	}
}

void drawLineOnScr(int xy[4], int hex) { // ...Using Bresnaham's line algo since 2024/20/04
	int x0, y0, x1, y1, dX, dY, deci, xIncr, yIncr, currX, currY;
	x0 = round(xy[0]);
	y0 = round(xy[1]);
	x1 = round(xy[2]);
	y1 = round(xy[3]);
	dX = abs(x1 - x0);
	dY = abs(y1 - y0);
	deci = 2 * dY - dX;
	xIncr = x0 < x1 ? 1 : -1;
	yIncr = y0 < y1 ? 1 : -1;
	currX = x0;
	currY = y0;
	setPixel(currX, currY, hex);
	int count = 0;
	while (count < dX) {
		if (deci > 0) {
			currY += yIncr;
			deci = deci - 2 * dX;
		}
		currX += xIncr;
		deci = deci + 2 * dY;
		setPixel(round(currX), round(currY), hex);
		count += 1;
	}
}

void EMSCRIPTEN_KEEPALIVE initScr() {
	scrArea = width * height;
	screen = (int*)malloc(scrArea * sizeof(int));
	fillRectOnScr(0, 0, width, height, initCol);
}

int EMSCRIPTEN_KEEPALIVE render(int frm) {
	int x, y;
	int audio = 0;
	fillRectOnScr(0, 0, width, height, initCol);
	fillRectOnScr(8, 8, 48, 48, 0xff0000);
	fillRectOnScr(44, 44, 32, 24, 0x00ff00);
	fillRectOnScr(8, 48, 32, 32, 0x0000ff);
	if ((frm % 16) < 8) {
		audio = 1000;
		fillRectOnScr(12, 128, 64, 24, 0x00ffff);
	}
	drawLineOnScr((int[]){2, 2, 12, 16}, 0x000000);
	return audio;
}

void EMSCRIPTEN_KEEPALIVE freeScr() {free(screen);}

int* EMSCRIPTEN_KEEPALIVE retScr() {return screen;}

int EMSCRIPTEN_KEEPALIVE getWidth() {return width;}

int EMSCRIPTEN_KEEPALIVE getHeight() {return height;}