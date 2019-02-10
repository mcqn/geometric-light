// Slant.h
// (c) Copyright 2017 MCQN Ltd.
//
// Slant design of animated Neopixel baubles
#ifndef SLANT_H
#define SLANT_H

#include "Bauble.h"

class Slant : public Bauble
{
public:
  static const int kSegmentLength = 49;
  static const int kInterSegmentGap = 2;
  static const int kFullLength = 3*kSegmentLength+2*kInterSegmentGap; // 151
public:
  Slant(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel);
protected:
  //virtual int getRandomPixel() { return iFirstPixel+50; };
  //virtual void climbing(int aColour);
  //virtual void falling(int aColour);
  //virtual void insideOut(int aColour);
  //virtual void outsideIn(int aColour);
public:
};

#endif
