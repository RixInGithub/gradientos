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
int lineX = 24;

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

void drawLineOnScr(int x0, int y0, int x1, int y1, int hex) { // Code from Wikipedia, fixed from previous algo since 2024/04/21.
	int dX, incrX, dY, incrY, err, err2;
	dX = abs(x1 - x0);
	incrX = x0 < x1 ? 1 : -1;
	dY = 0 - abs(y1 - y0);
	incrY = y0 < y1 ? 1 : -1;
	err = dX + dY;
	while (true) {
		setPixel(x0, y0, hex);
		if ((x0 == x1) && (y0 == y1)) break;
		err2 = err * 2;
		if (err2 >= dY) {
			if (x0 == x1) break;
			err = err + dY;
			x0 += incrX;
		}
		if (err2 <= dX) {
			if (y0 == y1) break;
			err = err + dX;
			y0 += incrY;
		}
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
	drawLineOnScr(2, 2, 12, 16, 0x000000);
	if (lineX > 200) lineX = 24;
	drawLineOnScr(lineX, 24, 128, 32, 0xff00ff);
	lineX += 1;
	drawLineOnScr(128, 128, 256, 128, 0x00ff80);
	return audio;
}

void EMSCRIPTEN_KEEPALIVE freeScr() {free(screen);}

int* EMSCRIPTEN_KEEPALIVE retScr() {return screen;}

int EMSCRIPTEN_KEEPALIVE getWidth() {return width;}

int EMSCRIPTEN_KEEPALIVE getHeight() {return height;}