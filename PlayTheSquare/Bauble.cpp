// Bauble.cpp
// (c) Copyright 2017 MCQN Ltd.
//
// Code for the base-class of animated Neopixel baubles
#include "Bauble.h"
#include "MakeColour.h"

// So we can include things like the sizes of the largest and
// smallest baubles, we'll include them here
#include "Bow.h"
#include "Chevron.h"
#include "Geostar.h"
#include "Icicle.h"
#include "Reflect.h"
#include "Rotosym.h"
#include "Slant.h"
#include "Star.h"
#include "Triangle.h"
#include "Tricorn.h"

const int kDefaultSaturation = 100;
const int kDefaultValue = 50;

// Colour palettes used by some of the bauble modes
const int kPrimaryPaletteSize = 3;
const int kPrimaryPalette[kPrimaryPaletteSize] = {
  0xff0000,
  0x00ff00,
  0x0000ff
};
const int kCMYKPaletteSize = 4;
const int kCMYKPalette[kCMYKPaletteSize] = {
  0x00ffff,
  0xffff00,
  0xff00ff,
  0x0
};
// A few palettes generated from http://tools.medialab.sciences-po.fr/iwanthue/
const int kIWHPaletteHard1Size = 8;
const int kIWHPaletteHard1[kIWHPaletteHard1Size] = {
  0x643e9c,
  0x53a903,
  0xcd43c6,
  0xb36b00,
  0x0170bd,
  0xfe2c68,
  0xa4c7ff,
  0xff95b0
};
const int kIWHPaletteHard2Size = 8;
const int kIWHPaletteHard2[kIWHPaletteHard2Size] = {
  0x8d6500,
  0x2b47ba,
  0x61c232,
  0xff6b94,
  0x009d83,
  0xffad53,
  0x028fd5,
  0xc8b600
};
const int kIWHPaletteHard3Size = 10;
const int kIWHPaletteHard3[kIWHPaletteHard3Size] = {
  0x00da4b,
  0xdc33e9,
  0x4fa700,
  0x0167f5,
  0x726a00,
  0x22cdff,
  0x9d0047,
  0x00bfa3,
  0xffa392,
  0x006a34
};
const int kIWHPaletteHard4Size = 6;
const int kIWHPaletteHard4[kIWHPaletteHard4Size] = {
  0x9e1a84,
  0xff3e62,
  0xb419ac,
  0xc92749,
  0xe746d4,
  0xc70088
};
const int kIWHPaletteHard5Size = 6;
const int kIWHPaletteHard5[kIWHPaletteHard5Size] = {
  0x0090b5,
  0x194968,
  0x3f9ba6,
  0x0086be,
  0x006e7d,
  0x5487b1
};
const int kIWHPaletteHard6Size = 6;
const int kIWHPaletteHard6[kIWHPaletteHard6Size] = {
  0x098922,
  0x86b733,
  0x00981c,
  0x75a100,
  0x39a600,
  0x559c00
};

const int kPaletteCount = 8;
const int kPaletteSizes[kPaletteCount] = {
  kPrimaryPaletteSize,
  kIWHPaletteHard1Size,
  kIWHPaletteHard2Size,
  kIWHPaletteHard3Size,
  kIWHPaletteHard4Size,
  kIWHPaletteHard5Size,
  kIWHPaletteHard6Size,
  kCMYKPaletteSize
};
const int* kPalettes[kPaletteCount] = {
  kPrimaryPalette,
  kIWHPaletteHard1,
  kIWHPaletteHard2,
  kIWHPaletteHard3,
  kIWHPaletteHard4,
  kIWHPaletteHard5,
  kIWHPaletteHard6,
  kCMYKPalette
};

Bauble::Bauble(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel, uint32_t aLastPixel)
  : iLEDs(aLEDs), iInterlaced(aInterlaced), iTouched(false), iSpacing(1+aInterlaced), iFirstPixel(aFirstPixel),
    // If we're in Interlaced mode, strips with odd numbered pixels 
    iLastPixel(aLastPixel-((aLastPixel-aFirstPixel)%iSpacing) ),
    iPattern(eFalling), iState(eAttract), iAttractMode(eAttractPalette), iCurrentColour(random(360)),
    iSensitivity(0.9), iColourVelocity(1.0), iCurrentPalette(kCMYKPalette), iCurrentPaletteSize(kCMYKPaletteSize)
{
  // Larger baubles have more area to cover and so should populate themselves more quickly
  // when in attract mode
  iAttractModeClockRate = map(constrain(aLastPixel-aFirstPixel, Icicle::kFullLength, Rotosym::kFullLength), Icicle::kFullLength, Rotosym::kFullLength, 4, 1);
  chooseRandomAttractMode();
}

void Bauble::setPattern(int aPattern) 
{
  iPattern = aPattern;
  if (iPattern == ePatternOff)
  {
    // We're switching off, so we need to do the state transition here too
    iState = eOff;
  }
  else if (iState == eOff)
  {
    // We're switching back on, so revert back to attract mode
    if (iTouched)
    {
      // Pretend we've just been touched
      iTouched = false;
      touched(true, 0);
    }
    else
    {
      iState = eAttract;
    }
  }
}

void Bauble::chooseRandomAttractMode()
{
  // Make each of the palettes as likely as one of the random modes
  iAttractMode = random(eAttractMax+kPaletteCount);
  if (iAttractMode >= eAttractMax)
  {
    iAttractMode = eAttractPalette;
    int palette = random(kPaletteCount);
    iCurrentPalette = kPalettes[palette];
    iCurrentPaletteSize = kPaletteSizes[palette];
  }
}

int Bauble::getRandomPixel()
{
  // Pick a random pixel
  int p = iFirstPixel+iSpacing*(random(iLastPixel-iFirstPixel)/iSpacing);
  return p;
}

void Bauble::fadeToBlackBy(int aFirstPixel, int aLastPixel, uint8_t aAmountLeft)
{
  for (int p = aFirstPixel; p <= aLastPixel; p++)
  {
    int col = iLEDs.getPixel(p);
    int r = ((col & 0xff0000)*aAmountLeft) >> 8 & 0xff0000;
    int g = ((col & 0x00ff00)*aAmountLeft) >> 8 & 0x00ff00;
    int b = ((col & 0x0000ff)*aAmountLeft) >> 8 & 0x0000ff;
    iLEDs.setPixel(p, r|g|b);
  }
}

bool Bauble::fadeToColourBy(int aFirstPixel, int aLastPixel, int aColour, uint8_t aAmountLeft)
{
  bool nothingChanged = true;
  for (int p = aFirstPixel; p <= aLastPixel; p++)
  {
    int col = iLEDs.getPixel(p);
    int r = (col & 0xff0000);
    int g = (col & 0x00ff00);
    int b = (col & 0x0000ff);
    if (p % iSpacing == 0)
    {
      // Fade these pixels to the right colour
      int currentHue = rgb2h(r, g, b);
if (p < aFirstPixel+5)
Serial.print(currentHue);
      int newHue;
      if (currentHue > aColour)
      {
        newHue = currentHue+((currentHue-aColour)*(255-aAmountLeft)/255.0);
        nothingChanged = false;
      }
      else if (currentHue < aColour)
      {
        newHue = currentHue-((aColour-currentHue)*(255-aAmountLeft)/255.0);
        nothingChanged = false;
      }
      iLEDs.setPixel(p, makeColor(newHue, kDefaultSaturation, kDefaultValue));
    }
    else
    {
      // Fade any interim pixels to black
      r = (r*aAmountLeft) >> 8 & 0xff0000;
      g = (g*aAmountLeft) >> 8 & 0x00ff00;
      b = (b*aAmountLeft) >> 8 & 0x0000ff;
      iLEDs.setPixel(p, r|g|b);
    }
  }
  return nothingChanged;
}

void Bauble::tickAttract(int aHueOffset)
{
  switch (iAttractMode)
  {
  case eAttractPalette:
    {
      if (iClock % kAttractFadeToBlackClockRate == 0)
      {
        fadeToBlackBy(iFirstPixel, iLastPixel, 230);
      }
      if (iClock % iAttractModeClockRate == 0)
      {
        // Make a random pixel a colour from the palette
        iLEDs.setPixel(getRandomPixel(), iCurrentPalette[random(iCurrentPaletteSize)]);
      }
    }
    break;
  case eAttractVarispeed:
    {
      if (iClock % kAttractFadeToBlackClockRate == 0)
      {
        fadeToBlackBy(iFirstPixel, iLastPixel, 230);
      }
      if (iClock % int(abs(sin(iClock*180/3.141592654))*10) == 0)
      {
        // Make a random pixel a random colour
        iLEDs.setPixel(getRandomPixel(), makeColor(random(360), random(kDefaultSaturation), random(kDefaultValue)));
      }
    }
    break;
  case eAttractRandom:
  default:
    {
      if (iClock % kAttractFadeToBlackClockRate == 0)
      {
        fadeToBlackBy(iFirstPixel, iLastPixel, 230);
      }
      if (iClock % iAttractModeClockRate == 0)
      {
        // Make a random pixel a random colour
        iLEDs.setPixel(getRandomPixel(), makeColor(random(360), random(kDefaultSaturation), random(kDefaultValue)));
      }
    }
    break;
  }
  // Every now and then switch modes
  if (random(8000) < 1)
  {
    iCountdownTicks = kFadeToBlackTicks;
    iState = eFadeToBlack;
  }
}
  
void Bauble::tick(int aHueOffset)
{
  switch (iState)
  {
  case eAttract:
    tickAttract(aHueOffset);
    break;
  case eOff:
    if (iClock % kFadeToBlackRate == 0)
    {
      fadeToBlackBy(iFirstPixel, iLastPixel, 230);
    }
    break;
  case eTouched:
    if (iClock % kTouchedClockRate == 0)
    {
      iCurrentColour = (iCurrentColour + (int)iColourVelocity) % 360;
      iColourAcceleration = iColourAcceleration+0.001;
      iColourVelocity = iColourVelocity+iColourAcceleration;
      if (iColourVelocity > 20)
        iColourVelocity = 20;
      pushColour((iCurrentColour + aHueOffset) % 360);
    }
    break;
  case eThrow:
    {
      if (iClock % kSlowClock == 0)
      {
        // s = u*t + 0.5*a*t*t
        int t = (iClock - iThrowStartTicks)/kSlowClock;
        iCurrentColour = iThrowStartColour + (iColourVelocity*t) + 0.5*iColourAcceleration*t*t;
        if (iCurrentColour < iThrowStartColour)
        {
          // We're back to where we started, start to timeout
          iState = eTimeout;
          iCountdownTicks = kTouchTimeout;
        }
        iCurrentColour = iCurrentColour % 360;
        pushColour((iCurrentColour + aHueOffset) % 360);
      }
    }
    break;
  case ePulsing:
    {
      if (iClock % kSlowClock == 0)
      {
        // Work out the colour we want right now
        int currentValue = constrain(iClock-iTouchStartTick, 0, 50);
        int colourNow = makeColor(iCurrentColour, kDefaultSaturation, currentValue);
        for (int p = iFirstPixel; p <= iLastPixel; p++)
        {
          if (p % iSpacing == 0)
          {
            // Bring these pixels up to the desired colour, or leave them at their current colour if it's higher
            iLEDs.setPixel(p, colourNow);
          }
          else
          {
            // Fade any interim pixels to black
            int col = iLEDs.getPixel(p);
            int r = (col & 0xff0000);
            int g = (col & 0x00ff00);
            int b = (col & 0x0000ff);
            r = (r*200) >> 8 & 0xff0000;
            g = (g*200) >> 8 & 0x00ff00;
            b = (b*200) >> 8 & 0x0000ff;
            iLEDs.setPixel(p, r|g|b);
          }
        }
        if (currentValue == 50)
        {
          // We've reached the colour
          iState = eFadeToBlack;
          iCountdownTicks = kFadeToBlackTicks;
        }
      }
    }
    break;
  case eTimeout:
    iCountdownTicks--;
    if (iClock % kTimeoutClockRate == 0)
    {
      pushColour((iCurrentColour + aHueOffset) % 360);
    }
    if (iCountdownTicks == 0)
    {
      // We've timed out...
      iCountdownTicks = kFadeToBlackTicks;
      iState = eFadeToBlack;
    }
    break;
  case eFadeToBlack:
    iCountdownTicks--;
    if (iClock % kFadeToBlackRate == 0)
    {
      fadeToBlackBy(iFirstPixel, iLastPixel, 230);
    }
    if (iCountdownTicks == 0)
    {
      if (random(100) < 5)
      {
        // Roughly one in twenty times we should switch to a different attract mode
        chooseRandomAttractMode();
      }
      if (random(100) < 5)
      {
        // Similarly change pattern every now and then
        setPattern(random(eClimbing, eBaubleMax));
      }
      iState = eAttract;
    }
    break;
  case eRftSPrep:
    // Wipe to black
    iLEDs.setPixel(iRftSPosition++, 0);
    if (iRftSPosition > iLastPixel)
    {
      // Done, onto the next stage
      iRftSPosition = iFirstPixel+(8*iSpacing); /* We don't want any gates *right* at the start */
      iState = eRftSSetGates;
    }
    break;
  case eRftSSetGates:
    {
      iRftSPosition+=iSpacing;
      if (iRftSPosition >= iLastPixel)
      {
        // Gates set!
        iRftSPosition = iFirstPixel;
        iRftSPowerUp = 0;
        iState = eRftSRun;
      }
      else if (random(20) == 1)
      {
        iLEDs.setPixel(iRftSPosition, iRftSGateColour);
        // Skip for the power-up time, so we can't make an impossible game
        iRftSPosition += kRftSPowerUpDistance;
      }
    }
    break;
  case eRftSRun:
    {
      if (iClock % iRftSClock == 0)
      {
        // Work out if we're in power-up or not
        int headColour = (iRftSPowerUp-- > 0) ? iRftSGateColour : iRftSHeadColour;
        if (iRftSPowerUp < 0)
        {
          iRftSPowerUp = 0;
        }
        int posColour = iLEDs.getPixel(iRftSPosition+iSpacing);
        // All is good
        iLEDs.setPixel(iRftSPosition, iRftSTailColour);
        iRftSPosition += iSpacing;
        if (iRftSPosition >= iLastPixel)
        {
          // We won!
          iState = eRftSSuccess;
        }
        else
        {
          iLEDs.setPixel(iRftSPosition, headColour);
          // Check for collision
          if ((posColour != headColour) && (posColour != 0))
          {
            // We've hit a gate :-(
            iState = eRftSFail;
            iCountdownTicks = kRftSFailCountdown;
          }
        }
        if (iRftSPosition % kRftSSpeedupThreshold == 0)
        {
          // Speed things up a bit to make it trickier...
          iRftSClock--;
        }
      }
    }
    break;
  case eRftSSuccess:
    {
      if (iClock % kSlowClock == 0)
      {
        iRftSPosition -= iSpacing;
        if (iRftSPosition <= iFirstPixel)
        {
          iState = eFadeToBlack;
          iCountdownTicks = kFadeToBlackTicks;
        }
        else
        {
          iLEDs.setPixel(iRftSPosition, makeColor(10*iRftSPosition % 360, kDefaultSaturation, kDefaultValue));
        }
      }
    }
    break;
  case eRftSFail:
    {
      if (iClock % kSlowClock == 0)
      {
        iCountdownTicks--;
        iLEDs.setPixel(iRftSPosition, makeColor(random(360), kDefaultSaturation, kDefaultValue));
        if (iCountdownTicks == 0)
        {
          iState = eFadeToBlack;
          iCountdownTicks = kFadeToBlackTicks;
        }
      }
    }
    break;
  }
  iClock++;
}

void Bauble::touched(bool aTouched, int aHueOffset)
{
  if (iPattern != eOff)
  {
    if ((iPattern != eReachForTheStar) && (iPattern != ePulse) && (iPattern != ePulse2) && (iPattern != ePulse3))
    {
      if (aTouched && (iState != eTouched))
      {
        // We've just been touched
        iState = eTouched;
        iTouchStartTick = iClock;
        // Reset our speed of change
        iColourVelocity = 1.0;
        iColourAcceleration = 0.02;
      }
      else if (!aTouched && (iState == eTouched))
      {
        // We've just stopped being touched
        if (iClock - iTouchStartTick < kShortTouchThreshold)
        {
          // It was a short touch, so "throw" the colour in the air
          iState = eThrow;
          iColourVelocity = 15;
          iColourAcceleration = -0.4;
          iThrowStartColour = iCurrentColour;
          iThrowStartTicks = iClock;
        }
        else
        {
          // Wait for a while before going back to attract mode
          iState = eTimeout;
          iCountdownTicks = kTouchTimeout;
        }
      }
    }
    else if ((iPattern == ePulse) || (iPattern == ePulse2) || (iPattern == ePulse3))
    {
      if (aTouched && (iState != ePulsing))
      {
        // We've just been touched
        iState = ePulsing;
        iTouchStartTick = iClock;
        iCurrentColour = random(360);
      }
      // For ePulse we only care about touched, not held or released
    }
    else
    {
      if (iState == eRftSRun)
      {
        if (!iTouched && aTouched && iRftSPowerUp == 0)
        {
          // We've just been touched and we aren't mid-power-up, so do a power up
          iRftSPowerUp = kRftSPowerUpDistance;
        }
      }
      if (aTouched && (iState < eRftSPrep))
      {
        // Start the game!
        // Choose the colours
        iRftSHeadColour = random(360);
        iRftSTailColour = makeColor((iRftSHeadColour + 120) % 360, kDefaultSaturation, kDefaultValue);
        iRftSGateColour = makeColor((iRftSHeadColour + 240) % 360, kDefaultSaturation, kDefaultValue);
        iRftSHeadColour = makeColor(iRftSHeadColour, kDefaultSaturation, kDefaultValue);
        iRftSPosition = iFirstPixel;
        iRftSClock = kRftSInitialClock;
        iState = eRftSPrep;
      }
    }
  }
  iTouched = aTouched;
}

void Bauble::pushColour(int aColour)
{
  //iCurrentColour = (iCurrentColour*(1.0-iSensitivity)) + (aColour*iSensitivity);
  switch (iPattern)
  {
  case eClimbing:
    climbing(makeColor(aColour, kDefaultSaturation, kDefaultValue));
    break;
  case eInsideOut:
    insideOut(makeColor(aColour, kDefaultSaturation, kDefaultValue));
    break;
  case eOutsideIn:
    outsideIn(makeColor(aColour, kDefaultSaturation, kDefaultValue));
    break;
  case eFalling:
  default:
    falling(makeColor(aColour, kDefaultSaturation, kDefaultValue));
    break;
  }
}

void Bauble::climbing(int aColour)
{
  // Shuffle all the LEDs along one
  for (uint32_t i = iLastPixel; i > iFirstPixel; i-=(1+iInterlaced))
  {
    iLEDs.setPixel(i, iLEDs.getPixel(i-(1+iInterlaced)));
  }
  iLEDs.setPixel(iFirstPixel, aColour);
}

void Bauble::falling(int aColour)
{
  // Shuffle all the LEDs along one
  for (uint32_t i = iFirstPixel; i <= iLastPixel; i+=iSpacing)
  {
    iLEDs.setPixel(i, iLEDs.getPixel(i+iSpacing));
  }
  iLEDs.setPixel(iLastPixel, aColour);
}

void Bauble::insideOut(int aColour)
{
  // If we've got an even number of pixels, we'll have two
  // different "middle" pixels
  uint32_t lowMidPixel = (iFirstPixel+iLastPixel)/2;
  uint32_t highMidPixel = ((iLastPixel-iFirstPixel) % 2 == 0) ? lowMidPixel + 1 : lowMidPixel;

  // Shuffle all the LEDs out by one...
  for (uint32_t i = iFirstPixel; i < lowMidPixel; i+=(1+iInterlaced))
  {
    iLEDs.setPixel(i, iLEDs.getPixel(i+(1+iInterlaced)));
  }
  for (uint32_t i = iLastPixel; i > highMidPixel; i-=(1+iInterlaced))
  {
    iLEDs.setPixel(i, iLEDs.getPixel(i-(1+iInterlaced)));
  }
  iLEDs.setPixel(lowMidPixel, aColour);
  iLEDs.setPixel(highMidPixel, aColour);
}

void Bauble::outsideIn(int aColour)
{
  // If we've got an even number of pixels, we'll have two
  // different "middle" pixels
  uint32_t lowMidPixel = (iFirstPixel+iLastPixel)/2;
  uint32_t highMidPixel = ((iLastPixel-iFirstPixel) % 2 == 0) ? lowMidPixel + 1 : lowMidPixel;

  // Shuffle all the LEDs in by one...
  for (uint32_t i = lowMidPixel; i > iFirstPixel; i-=iSpacing)
  {
    iLEDs.setPixel(i, iLEDs.getPixel(i-iSpacing));
  }
  for (uint32_t i = highMidPixel; i < iLastPixel; i+=iSpacing)
  {
    iLEDs.setPixel(i, iLEDs.getPixel(i+iSpacing));
  }
  iLEDs.setPixel(iFirstPixel+iInterlaced, aColour);
  iLEDs.setPixel(iLastPixel, aColour);
}


