// Geostar.h
// (c) Copyright 2017 MCQN Ltd.
//
// Geostar design of animated Neopixel baubles
#ifndef GEOSTAR_H
#define GEOSTAR_H

#include "Bauble.h"

class Geostar : public Bauble
{
public:
  static const int kMiddleLength = 9;
  static const int kShortLength = 19;
  static const int kMidLength = 36;
  static const int kLongLength = 60;
  static const int kInterSegmentGap = 2;
  static const int kFullLength = 4*(43+18+6+2*kInterSegmentGap)+3*kInterSegmentGap; // 290
public:
  Geostar(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel);
protected:
  //virtual int getRandomPixel() { return iFirstPixel+50; };
  //virtual void climbing(int aColour);
  //virtual void falling(int aColour);
  //virtual void insideOut(int aColour);
  //virtual void outsideIn(int aColour);
public:
};

#endif
