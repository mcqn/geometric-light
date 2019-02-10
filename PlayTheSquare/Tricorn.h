// Tricorn.h
// (c) Copyright 2017 MCQN Ltd.
//
// Tricorn design of animated Neopixel baubles
#ifndef TRICORN_H
#define TRICORN_H

#include "Bauble.h"

class Tricorn : public Bauble
{
public:
  static const int kMiddleLength = 39;
  static const int kShortLength = 28;
  static const int kInterSegmentGap = 2;
  static const int kFullLength = 3*(2*kShortLength+2*kInterSegmentGap+kMiddleLength)+2*kInterSegmentGap; // 301
public:
  Tricorn(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel);
protected:
  //virtual int getRandomPixel() { return iFirstPixel+50; };
  //virtual void climbing(int aColour);
  //virtual void falling(int aColour);
  //virtual void insideOut(int aColour);
  //virtual void outsideIn(int aColour);
public:
};

#endif
