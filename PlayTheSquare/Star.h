// Star.h
// (c) Copyright 2017 MCQN Ltd.
//
// Star design of animated Neopixel baubles
#ifndef STAR_H
#define STAR_H

#include "Bauble.h"

class Star : public Bauble
{
public:
  static const int kSegmentLength = 69;
  static const int kInterSegmentGap = 2;
  static const int kFullLength = 4*kSegmentLength+3*kInterSegmentGap; // 282
public:
  Star(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel);
protected:
  //virtual int getRandomPixel() { return iFirstPixel+50; };
  //virtual void climbing(int aColour);
  //virtual void falling(int aColour);
  //virtual void insideOut(int aColour);
  //virtual void outsideIn(int aColour);
public:
};

#endif
