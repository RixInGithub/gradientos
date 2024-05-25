#include "wins.h"
#include <string.h>

char wins_titles[256][256];

void wins_add(const char *title) {
	int index = -1;
	int count = 0;
	while (count < 256) {
		if (wins_titles[count][0] == "\0") {
			index = count;
			break;
		}
		count += 1;
	}
	if (index < 0) return;
	strncpy(wins_titles[index], title, 255);
	wins_titles[index][255] = "\0";
}

void wins_remove(int index) {
	if ((index >= 0) && (index < 256)) {
		wins_titles[index][0] = "\0";
	}
}
