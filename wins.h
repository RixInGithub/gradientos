#ifndef WINS_H
#define WINS_H
extern char wins_titles[256][256];

void wins_add(const char *title);
void wins_remove(int index);
#endif