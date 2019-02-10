// Chevron.h
// (c) Copyright 2017 MCQN Ltd.
//
// Base-class of animated Neopixel baubles
#ifndef CHEVRON_H
#define CHEVRON_H

#include "Bauble.h"

class Chevron : public Bauble
{
public:
  static const int kPixelsPerSegment = 37;
  static const int kInterSegmentGap = 2;
  static const int kRowCount = 3;
  // Indexes into the segment array
  static const int kTopRow = 0;
  static const int kMiddleRow = 1;
  static const int kBottomRow = 2;
  static const int kFullLength = kPixelsPerSegment*6+kInterSegmentGap*5;
public:
  Chevron(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel);
protected:
  //virtual void climbing(int aColour);
  //virtual void falling(int aColour);
  //virtual void insideOut(int aColour);
  //virtual void outsideIn(int aColour);
public:
  int iSegments[kRowCount][2];
};

#endif
