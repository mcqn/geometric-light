#ifndef MAKECOLOUR_H
#define MAKECOLOUR_H

extern unsigned int h2rgb(unsigned int v1, unsigned int v2, unsigned int hue);
extern int makeColor(unsigned int hue, unsigned int saturation, unsigned int lightness);
extern unsigned int rgb2h(unsigned int R, unsigned int G, unsigned int B);

#endif
