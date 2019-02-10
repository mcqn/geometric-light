// Triangle.h
// (c) Copyright 2017 MCQN Ltd.
//
// Triangle design of animated Neopixel baubles
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Bauble.h"

class Triangle : public Bauble
{
public:
  static const int kMiddleLength = 9;
  static const int kShortLength = 19;
  static const int kMidLength = 36;
  static const int kLongLength = 60;
  static const int kInterSegmentGap = 2;
  static const int kFullLength = 7+17+25+32+41+48+57+6*kInterSegmentGap; // 239
public:
  Triangle(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel);
protected:
  //virtual int getRandomPixel() { return iFirstPixel+50; };
  //virtual void climbing(int aColour);
  //virtual void falling(int aColour);
  //virtual void insideOut(int aColour);
  //virtual void outsideIn(int aColour);
public:
};

#endif
