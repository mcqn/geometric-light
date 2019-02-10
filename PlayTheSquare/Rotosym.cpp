// Rotosym.cpp
// (c) Copyright 2017 MCQN Ltd.
//
// Code for the Rotosym animated Neopixel baubles
#include "Rotosym.h"
#include "MakeColour.h"

Rotosym::Rotosym(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel)
    : Bauble(aLEDs, aInterlaced, aFirstPixel, aFirstPixel+kFullLength)
{
  // Default to touched
  iTouched = true;
  iState = eTouched;
  iColourVelocity = 1.0;
  iColourAcceleration = 0.02;
}

void Rotosym::tick(int aHueOffset)
{
  switch (iState)
  {
  case eOff:
    if (iClock % kFadeToBlackRate == 0)
    {
      fadeToBlackBy(iFirstPixel, iLastPixel, 230);
    }
    // Reset rainbow speed for when we're next turned on
    iColourVelocity = 1.0;
    iColourAcceleration = 0.02;
    break;
  // Rotosym is only either off or running through the rainbow
  default:
    if (iClock % 5 == 0)
    {
      iCurrentColour = (iCurrentColour + (int)iColourVelocity) % 360;
      iColourAcceleration = iColourAcceleration+0.001;
      iColourVelocity = iColourVelocity+iColourAcceleration;
      if (iColourVelocity > 20)
        iColourVelocity = 20;
      pushColour((iCurrentColour + aHueOffset) % 360);
    }
    break;
  }
  iClock++;
}

