// Icicle.h
// (c) Copyright 2017 MCQN Ltd.
//
// Icicle design of animated Neopixel baubles
#ifndef ICICLE_H
#define ICICLE_H

#include "Bauble.h"

class Icicle : public Bauble
{
public:
  static const int kInterSegmentGap = 2;
  static const int kFullLength = 61;
public:
  Icicle(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel);
protected:
  //virtual int getRandomPixel() { return iFirstPixel+50; };
  //virtual void climbing(int aColour);
  //virtual void falling(int aColour);
  //virtual void insideOut(int aColour);
  //virtual void outsideIn(int aColour);
public:
};

#endif
