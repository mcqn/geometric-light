// Chevron.cpp
// (c) Copyright 2017 MCQN Ltd.
//
// Code for the base-class of animated Neopixel baubles
#include "Chevron.h"
#include "MakeColour.h"

Chevron::Chevron(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel)
    : Bauble(aLEDs, aInterlaced, aFirstPixel, aFirstPixel+kFullLength)
{
  // Set up the segment array of where the pixel offsets are
  iSegments[kTopRow][0] = aFirstPixel+iInterlaced;
  iSegments[kTopRow][1] = iSegments[kTopRow][0]+kPixelsPerSegment+kInterSegmentGap;
  iSegments[kMiddleRow][0] = iSegments[kTopRow][1]+kPixelsPerSegment+kInterSegmentGap;
  iSegments[kMiddleRow][1] = iSegments[kMiddleRow][0]+kPixelsPerSegment+kInterSegmentGap;
  iSegments[kBottomRow][0] = iSegments[kMiddleRow][1]+kPixelsPerSegment+kInterSegmentGap;
  iSegments[kBottomRow][1] = iSegments[kBottomRow][0]+kPixelsPerSegment+kInterSegmentGap;
}

#if 0
void Chevron::climbing(int aColour)
{
  // Shuffle all the LEDs down one
  // Bottom row first
  for (int i = kBottomRow; i >= kTopRow; i--)
  {
    for (int j = 0; j < kPixelsPerSegment-1; j+=(1+iInterlaced))
    {
      // First segment on the row starts at the low point
      iLEDs.setPixel(iSegments[i][0]+j, iLEDs.getPixel(iSegments[i][0]+j+1+iInterlaced));
      // Second segment on the row starts at the high point
      iLEDs.setPixel(iSegments[i][1]+kPixelsPerSegment-j, iLEDs.getPixel(iSegments[i][1]+kPixelsPerSegment-(j+1+iInterlaced)));
    }
    // For the top LED of each segment, take the bottom one of the segment above
    if (i > kTopRow)
    {
      iLEDs.setPixel(iSegments[i][0]+kPixelsPerSegment-1, iLEDs.getPixel(iSegments[i-1][0]));
      iLEDs.setPixel(iSegments[i][1], iLEDs.getPixel(iSegments[i-1][1]+kPixelsPerSegment));
    }
  }
  iLEDs.setPixel(iSegments[kTopRow][0]+kPixelsPerSegment-(1+iInterlaced), 1234);
  iLEDs.setPixel(iSegments[kTopRow][1], aColour);
}
#endif

