// Rotosym.h
// (c) Copyright 2017 MCQN Ltd.
//
// Rotosym design of animated Neopixel baubles
#ifndef ROTOSYM_H
#define ROTOSYM_H

#include "Bauble.h"

class Rotosym : public Bauble
{
public:
  static const int kShortLength = 12;
  static const int kMidLength = 24;
  static const int kLongLength = 42;
  static const int kInterSegmentGap = 2;
  static const int kFullLength = 4*(kLongLength+kInterSegmentGap+kMidLength+kInterSegmentGap+kShortLength)+3*kInterSegmentGap; // 334
public:
  Rotosym(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel);
  virtual void tick(int aHueOffset);
protected:
  //virtual int getRandomPixel() { return iFirstPixel+50; };
  //virtual void climbing(int aColour);
  //virtual void falling(int aColour);
  //virtual void insideOut(int aColour);
  //virtual void outsideIn(int aColour);
public:
};

#endif
