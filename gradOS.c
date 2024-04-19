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

void EMSCRIPTEN_KEEPALIVE initScr() {
	scrArea = width * height;
	screen = (int*)malloc(scrArea * sizeof(int));
	fillRectOnScr(0, 0, width, height, initCol);
}

void EMSCRIPTEN_KEEPALIVE render(int frm) {
	int x, y;
	fillRectOnScr(0, 0, width, height, initCol);
	fillRectOnScr(8, 8, 48, 48, 0xff0000);
	fillRectOnScr(44, 44, 32, 24, 0x00ff00);
	fillRectOnScr(8, 48, 32, 32, 0x0000ff);
	if ((frm % 16) < 8) {
		fillRectOnScr(12, 128, 64, 24, 0x00ffff);
	}
}

void EMSCRIPTEN_KEEPALIVE freeScr() {free(screen);}

int* EMSCRIPTEN_KEEPALIVE retScr() {return screen;}

int EMSCRIPTEN_KEEPALIVE getWidth() {return width;}

int EMSCRIPTEN_KEEPALIVE getHeight() {return height;}