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
	The JS source code is located at https://gradientos.neocities.org/wasm.js
*/
#include <stdio.h>
#include <emscripten.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "wins.h"
#define TXT_BORD 1 // Cell bottom padding, border width, and margin
#define TXT_H    (10 + (TXT_BORD * 3))
#define CELLS    4

int width = 384;
int height = 216;
int scrArea;
int *screen;
int appSelH = 4 + ((TXT_H * (CELLS - 1)) + 10); // 4 = (((border width <1>) * 2) * 2)
int initCol = 0x808080;
int mouseX = 0;
int mouseY = 0;
bool isDown = false;
int activeWin = -1;

// clang-format off
EM_JS(char*, netGet, (char* url), {
	// Definition in JS source
})
EM_JS(void, drawLett, (int x, int y, char ch, int hex), {
	// Definition in JS source
})
EM_JS(int, getLettW, (char ch), {
	// Definition in JS source
})
EM_JS(void, print, (char* txt), {
	// Definition in JS source
	// This function is only here for debugging purposes.
	// Example: print("Hello, world!");
})
// clang-format on

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

void writeStr(int x, int y, char* str, int hex) {
	int lettCount = x;
	int count = 0;
	int lettW;
	char ch;
	while (str[count] != *"\0") {
		ch = (char)str[count];
		lettW = getLettW(ch);
		drawLett(lettCount, y, ch, hex);
		lettCount += lettW;
		lettCount += 1;
		count += 1;
	}
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

void EMSCRIPTEN_KEEPALIVE init() {
	print("Screen initialized.");
	scrArea = width * height;
	screen = (int*)malloc(scrArea * sizeof(int));
	fillRectOnScr(0, 0, width, height, initCol);
	// netGet("https://google.com"); Seems like this thing works fine; will work on return checks pretty soon.
	
}

int EMSCRIPTEN_KEEPALIVE render(int frm) {
	int x, y;
	int audio = 0;
	bool down = isDown;
	if (isDown) {audio = 1000;}
	fillRectOnScr(0, 0, width, appSelH, 0xff00ff);
	return audio;
}

void EMSCRIPTEN_KEEPALIVE freeScr() {free(screen);}

int* EMSCRIPTEN_KEEPALIVE retScr() {return screen;}

int EMSCRIPTEN_KEEPALIVE getWidth() {return width;}

int EMSCRIPTEN_KEEPALIVE getHeight() {return height;}

void EMSCRIPTEN_KEEPALIVE setMouseXY(int x, int y) {
	mouseX = x;
	mouseY = y;
}

void EMSCRIPTEN_KEEPALIVE setMouseDown(bool smth) {
	isDown = smth;
}