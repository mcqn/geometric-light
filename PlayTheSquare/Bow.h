// Bow.h
// (c) Copyright 2017 MCQN Ltd.
//
// Bow design of animated Neopixel baubles
#ifndef BOW_H
#define BOW_H

#include "Bauble.h"

class Bow : public Bauble
{
public:
  static const int kMiddleLength = 9;
  static const int kShortLength = 19;
  static const int kMidLength = 36;
  static const int kLongLength = 60;
  static const int kInterSegmentGap = 2;
  static const int kFullLength = kMiddleLength+2*(kShortLength+kInterSegmentGap+kMidLength+kInterSegmentGap+kLongLength+kInterSegmentGap); // 251
public:
  Bow(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel);
protected:
  //virtual int getRandomPixel() { return iFirstPixel+50; };
  //virtual void climbing(int aColour);
  //virtual void falling(int aColour);
  //virtual void insideOut(int aColour);
  //virtual void outsideIn(int aColour);
public:
};

#endif
