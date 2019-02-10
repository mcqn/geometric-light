// Reflect.cpp
// (c) Copyright 2017 MCQN Ltd.
//
// Code for the Reflect animated Neopixel baubles
#include "Reflect.h"
#include "MakeColour.h"

Reflect::Reflect(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel)
    : Bauble(aLEDs, aInterlaced, aFirstPixel, aFirstPixel+kFullLength)
{
  // Set up the segment array of where the pixel offsets are
  iSegments[kMiddle] = aFirstPixel+iInterlaced;
  iSegments[kFirstLong] = aFirstPixel+iInterlaced+114;
  iSegments[kFirstMid] = aFirstPixel+iInterlaced+160;
  iSegments[kFirstShort] = aFirstPixel+iInterlaced+192;
  iSegments[kSecondShort] = aFirstPixel+iInterlaced+212;
  iSegments[kSecondMid] = aFirstPixel+iInterlaced+231;
  iSegments[kSecondLong] = aFirstPixel+iInterlaced+264;
  iFanOutPositions[kMiddle] = iSegments[kMiddle]+kMiddleLength/2;
  iFanOutPositions[kFirstLong] = iSegments[kMiddle]+60;
  iFanOutPositions[kFirstMid] = iSegments[kMiddle]+62;
  iFanOutPositions[kFirstShort] = iSegments[kMiddle]+64;
  iFanOutPositions[kSecondShort] = iSegments[kMiddle]+48;
  iFanOutPositions[kSecondMid] = iSegments[kMiddle]+50;
  iFanOutPositions[kSecondLong] = iSegments[kMiddle]+52;
}

void Reflect::insideOut(int aColour)
{
  // Fan out the middle
  for (int i = 0; i < kMiddleLength/2; i+=iSpacing)
  {
    iLEDs.setPixel(iSegments[kMiddle]+i, iLEDs.getPixel(iSegments[kMiddle]+iSpacing+i));
    iLEDs.setPixel(iSegments[kMiddle]+kMiddleLength-1-i, iLEDs.getPixel(iSegments[kMiddle]+kMiddleLength-1-(i+iSpacing)));
  }
  // Now fan out the long segments
  for (int j = 0; j < kLongLength; j+=iSpacing)
  {
    // First long segment starts at the outside
    iLEDs.setPixel(iSegments[kFirstLong]+iInterlaced+j, iLEDs.getPixel(iSegments[kFirstLong]+iInterlaced+j+iSpacing));
    // Second long segment middle
    iLEDs.setPixel(iSegments[kSecondLong]+kLongLength+iInterlaced-j, iLEDs.getPixel(iSegments[kSecondLong]+kLongLength+iInterlaced-(j+iSpacing)));
  }
  // Seed the long segments from the right point on the middle segment
  iLEDs.setPixel(iSegments[kFirstLong]+kLongLength, iLEDs.getPixel(iFanOutPositions[kFirstLong]));
  iLEDs.setPixel(iSegments[kSecondLong], iLEDs.getPixel(iFanOutPositions[kSecondLong]));
  // Now fan out the mid segments
  for (int j = 0; j < kMidLength; j+=iSpacing)
  {
    // First mid segment middle
    iLEDs.setPixel(iSegments[kFirstMid]+kMidLength-j, iLEDs.getPixel(iSegments[kFirstMid]+kMidLength-(j+iSpacing)));
    // Second mid segment starts at the outside
    iLEDs.setPixel(iSegments[kSecondMid]+j, iLEDs.getPixel(iSegments[kSecondMid]+j+iSpacing));
  }
  // Seed the mid segments from the right point on the middle segment
  iLEDs.setPixel(iSegments[kFirstMid], iLEDs.getPixel(iFanOutPositions[kFirstMid]));
  iLEDs.setPixel(iSegments[kSecondMid]+kMidLength, iLEDs.getPixel(iFanOutPositions[kSecondMid]));
  // Now fan out the short segments
  for (int j = 0; j < kShortLength; j+=iSpacing)
  {
    // First short segment starts at the outside
    iLEDs.setPixel(iSegments[kFirstShort]+j, iLEDs.getPixel(iSegments[kFirstShort]+j+iSpacing));
    // Second short segment starts at the middle
    iLEDs.setPixel(iSegments[kSecondShort]+kShortLength-j, iLEDs.getPixel(iSegments[kSecondShort]+kShortLength-(j+iSpacing)));
  }
  // Seed the short segments from the right point on the middle segment
  iLEDs.setPixel(iSegments[kFirstShort]+kShortLength, iLEDs.getPixel(iFanOutPositions[kFirstShort]));
  iLEDs.setPixel(iSegments[kSecondShort], iLEDs.getPixel(iFanOutPositions[kSecondShort]));

  iLEDs.setPixel(iSegments[kMiddle]+kMiddleLength/2, aColour);
}

void Reflect::outsideIn(int aColour)
{
  // Fan in the middle
  for (int i = kMiddleLength/2; i > 0; i-=iSpacing)
  {
    iLEDs.setPixel(iSegments[kMiddle]+i, iLEDs.getPixel(iSegments[kMiddle]+i-iSpacing));
    iLEDs.setPixel(iSegments[kMiddle]+kMiddleLength-1-i, iLEDs.getPixel(iSegments[kMiddle]+kMiddleLength-1-(i-iSpacing)));
  }
  // Now fan in the long segments
  for (int j = kLongLength; j > 0; j-=iSpacing)
  {
    // First long segment starts at the outside
    iLEDs.setPixel(iSegments[kFirstLong]+iInterlaced+j, iLEDs.getPixel(iSegments[kFirstLong]+iInterlaced+j-iSpacing));
    // Second long segment middle
    iLEDs.setPixel(iSegments[kSecondLong]+kLongLength+iInterlaced-j, iLEDs.getPixel(iSegments[kSecondLong]+kLongLength+iInterlaced-(j-iSpacing)));
  }
  // Seed the long segments from the right point on the middle segment
  iLEDs.setPixel(iSegments[kFirstLong], aColour);
  iLEDs.setPixel(iSegments[kSecondLong]+kLongLength, aColour);
  // Now fan in the mid segments
  for (int j = kMidLength; j > 0; j-=iSpacing)
  {
    // First mid segment middle
    iLEDs.setPixel(iSegments[kFirstMid]+kMidLength-j, iLEDs.getPixel(iSegments[kFirstMid]+kMidLength-(j-iSpacing)));
    // Second mid segment starts at the outside
    iLEDs.setPixel(iSegments[kSecondMid]+j, iLEDs.getPixel(iSegments[kSecondMid]+j-iSpacing));
  }
  // Seed the mid segments from the right point on the middle segment
  iLEDs.setPixel(iSegments[kFirstMid]+kMidLength, aColour);
  iLEDs.setPixel(iSegments[kSecondMid], aColour);
  // Now fan in the short segments
  for (int j = kShortLength; j > 0; j-=iSpacing)
  {
    // First short segment starts at the outside
    iLEDs.setPixel(iSegments[kFirstShort]+j, iLEDs.getPixel(iSegments[kFirstShort]+j-iSpacing));
    // Second short segment starts at the middle
    iLEDs.setPixel(iSegments[kSecondShort]+kShortLength-j, iLEDs.getPixel(iSegments[kSecondShort]+kShortLength-(j-iSpacing)));
  }
  // Seed the short segments from the right point on the middle segment
  iLEDs.setPixel(iSegments[kFirstShort], aColour);
  iLEDs.setPixel(iSegments[kSecondShort]+kShortLength, aColour);

  iLEDs.setPixel(iSegments[kMiddle]+kMiddleLength-iInterlaced, aColour);
  iLEDs.setPixel(iSegments[kMiddle], aColour);
}


