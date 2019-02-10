// Bauble.h
// (c) Copyright 2017 MCQN Ltd.
//
// Base-class of animated Neopixel baubles
#ifndef BAUBLE_H
#define BAUBLE_H

#include <OctoWS2811.h>

class Bauble
{
// Constants and types
public:
  // Animation patterns
  enum {
    eReachForTheStar,
    ePatternOff,
    eClimbing,
    eFalling,
    eInsideOut,
    eOutsideIn,
    ePulse,
    ePulse2,
    ePulse3,
    eBaubleMax
  };
  enum {
    eAttract,
    eOff,
    eFadeToBlack,
    eThrow,
    eTimeout,
    eTouched,
    ePulsing,
    // Non-RftS states should go before here
    eRftSPrep,
    eRftSSetGates,
    eRftSRun,
    eRftSSuccess,
    eRftSFail,
    eStateMax
  };
  // Attract modes
  enum {
    eAttractRandom,
    eAttractPalette,
    eAttractVarispeed,
    eAttractMax
  };
  // How many ticks before the timeout state times out
  const unsigned int kTouchTimeout = 1000;
  // How many ticks before we'll have faded to black
  const unsigned int kFadeToBlackTicks = 180;
  // How many ticks before each fade to black
  const unsigned int kFadeToBlackRate = 5;
  // How many ticks in attract mode we should count before one tick of fade to black
  const unsigned int kAttractFadeToBlackClockRate = 10;
  // How many ticks before a touch event isn't a short one
  const unsigned int kShortTouchThreshold = 300;
#ifdef INTERLACED
  // How many ticks we should count before one tick of the "slow" clock
  const unsigned int kSlowClock = 3;
  // How many ticks we should count before one tick of the clock when touched
  const unsigned int kTouchedClockRate = 2;
  // How many ticks we should count before one tick of the clock when touched
  const unsigned int kTimeoutClockRate = 5;
#else
  // How many ticks we should count before one tick of the "slow" clock
  const unsigned int kSlowClock = 1;
  // How many ticks we should count before one tick of the clock when touched
  const unsigned int kTouchedClockRate = 1;
  // How many ticks we should count before one tick of the clock when touched
  const unsigned int kTimeoutClockRate = 3;
#endif
  // How fast the RftS game should start out
  const unsigned int kRftSInitialClock = 20;
  // How many positions along we should make the RftS game run faster
  const int kRftSSpeedupThreshold = 50;
  // Number of pixels along which to have a power-up
  const int kRftSPowerUpDistance = 4;
  // How many ticks the failure animation will run through
  const int kRftSFailCountdown = 50;

// Methods
public:
  Bauble(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel, uint32_t aLastPixel);
  virtual void pushColour(int aColour);
  void setPattern(int aPattern);
  // Set how sensitive to new colours the bauble is
  //   aSensitivity - 0.1 for low sensitivity, 1.0 for most sensitive
  void setSensitivity(float aSensitivity) { iSensitivity = aSensitivity; };
  void touched(bool aTouched, int aHueOffset);
  // 
  virtual void tick(int aHueOffset);
  virtual void chooseRandomAttractMode();
protected:
  // Choose a random pixel for this bauble
  // NOTE: In interlaced mode sub-classes might need to more cleverly pick pixels
  //       to cope with different segments being aligned on different odd or even boundaries
  virtual int getRandomPixel();
  // Fade a series of pixels towards black
  virtual void fadeToBlackBy(int aFirstPixel, int aLastPixel, uint8_t aAmountLeft);
  // Fade a series of pixels towards a given colour
  // Return true if the colour has been reached, else false
  virtual bool fadeToColourBy(int aFirstPixel, int aLastPixel, int aColour, uint8_t aAmountLeft);
  virtual void climbing(int aColour);
  virtual void falling(int aColour);
  virtual void insideOut(int aColour);
  virtual void outsideIn(int aColour);
  virtual void tickAttract(int aHueOffset);
// Member variables
protected:
  OctoWS2811& iLEDs;
  bool iInterlaced;
  bool iTouched;
  int iSpacing; // Gap between pixels, either 1 or 2
  uint32_t iFirstPixel;
  uint32_t iLastPixel;
  int iPattern;
  int iState;
  int iAttractMode;
  unsigned int iTouchStartTick;
  unsigned int iCountdownTicks;
  int iCurrentColour;
  int iThrowStartColour;
  unsigned int iThrowStartTicks;
  float iSensitivity;
  float iColourVelocity;
  float iColourAcceleration;
  const int* iCurrentPalette;
  int iCurrentPaletteSize;
  unsigned int iClock;
  unsigned int iSpeed;
  unsigned int iAttractModeClockRate;
  // Reach for the Star variables
  int iRftSHeadColour;
  int iRftSTailColour;
  int iRftSGateColour;
  int iRftSPosition;
  int iRftSPowerUp;
  int iRftSClock;
};

#endif
