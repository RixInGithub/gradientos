#ifndef WINS_H
#define WINS_H
#include <stdbool.h>

typedef struct {
	int pos[2];
	char title[256];
} Window;

void wins_moveByOffset(Window *window, int xOffset, int yOffset);

Window wins_new(int x, int y, char title[]);

#endif