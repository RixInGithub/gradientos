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

void getXYFrom1D(int px, int *x, int *y) {
	*x = px % width;
	*y = (int)floor((double)px / width);
}

int get1DFromXY(int x, int y) {
	return y * width + x;
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
			screen[get1DFromXY(x + xCnt, y + yCnt)] = hex;
			xCnt += 1;
		}
		yCnt += 1;
	}
}

void EMSCRIPTEN_KEEPALIVE displayImg(int img[]) {
	int count = 0;
	while (count < scrArea) {
		screen[count] = img[count];
		count += 1;
	}
}

void EMSCRIPTEN_KEEPALIVE initScr() {
	scrArea = width * height;
	int count = 0;
	screen = (int*)malloc(scrArea * sizeof(int));
	while (count < scrArea) {
		screen[count] = 0x008080;
		count += 1;
	}
}

void EMSCRIPTEN_KEEPALIVE render(int frm) {
	int x, y;
	fillRectOnScr(8, 8, 48, 48, 0xff0000);
	fillRectOnScr(44, 44, 32, 24, 0x00ff00);
	fillRectOnScr(8, 48, 32, 32, 0x0000ff);
	fillRectOnScr(12, 128, 64, 24, 0x00ffff);
}

void EMSCRIPTEN_KEEPALIVE freeScr() {free(screen);}

int* EMSCRIPTEN_KEEPALIVE retScr() {return screen;}

int EMSCRIPTEN_KEEPALIVE getWidth() {return width;}

int EMSCRIPTEN_KEEPALIVE getHeight() {return height;}