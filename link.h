#ifndef LINK_H
#define LINK_H

extern int links[24][24];

void lock_links(int r, int c, int player);

int join(int i, int j, int c);

#endif