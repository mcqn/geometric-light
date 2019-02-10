// Reflect.h
// (c) Copyright 2017 MCQN Ltd.
//
// Reflect design of animated Neopixel baubles
#ifndef REFLECT_H
#define REFLECT_H

#include "Bauble.h"

class Reflect : public Bauble
{
public:
  static const int kMiddleLength = 113;
  static const int kShortLength = 18;
  static const int kMidLength = 30;
  static const int kLongLength = 43;
  static const int kInterSegmentGap = 2;
  static const int kFullLength = kMiddleLength+2*(kShortLength+kInterSegmentGap+kMidLength+kInterSegmentGap+kLongLength+kInterSegmentGap); // 307
  // Indices into the segment array
  static const int kMiddle = 0;
  static const int kFirstLong = 1;
  static const int kFirstMid = 2;
  static const int kFirstShort = 3;
  static const int kSecondShort = 4;
  static const int kSecondMid = 5;
  static const int kSecondLong = 6;
  static const int kSegmentCount = 7;
public:
  Reflect(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel);
protected:
  //virtual int getRandomPixel() { return iFirstPixel+50; };
  //virtual void climbing(int aColour);
  //virtual void falling(int aColour);
  virtual void insideOut(int aColour);
  virtual void outsideIn(int aColour);
public:
  int iSegments[kSegmentCount];
  int iSegmentEnds[kSegmentCount];
  // Indices into the middle segment from which the centre radiates onto other segments
  int iFanOutPositions[kSegmentCount];
};

#endif
