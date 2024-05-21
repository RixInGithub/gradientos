#include "wins.h"
#include <stdbool.h>

void wins_moveByOffset(Window *win, int xOffset, int yOffset) {
	win->pos[0] += xOffset;
	win->pos[1] += yOffset;
}

Window wins_new(int x, int y, char title[]) {
	Window res = {{x, y}, *title};
	return res;
}