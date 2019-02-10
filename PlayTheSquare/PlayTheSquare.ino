// PlayTheSquare
// (c) Copyright 2017 MCQN Ltd
#include <OctoWS2811.h>
#include "TouchSensor.h"
#include "Bauble.h"
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
#include "MakeColour.h"

//#define INTERLACED
#ifdef INTERLACED
bool gInterlaced = true;
#else
bool gInterlaced = false;
#endif

// For the install we'll have four Teensy boards
// This is how we identify which is which
// Use ID of 0 for install in order to light up all of the baubles fully
#define TEENSY_ID 0

// The Rotosym is the longest strip we'll be connecting, so make sure we've enough space for it (plus a margin)
const int kLedsPerStrip = Rotosym::kFullLength+Icicle::kFullLength+50;

DMAMEM int gDisplayMemory[kLedsPerStrip*6];
int gDrawingMemory[kLedsPerStrip*6];

const int gLedConfig = WS2811_GRB | WS2811_800kHz;
OctoWS2811 gLeds(kLedsPerStrip, gDisplayMemory, gDrawingMemory, gLedConfig, gInterlaced);

#if TEENSY_ID == 0
// Maximum baubles for easier checking of LEDs...
Rotosym  r1(gLeds, gInterlaced, 0*kLedsPerStrip+1);
Icicle   b1(gLeds, gInterlaced, 1*kLedsPerStrip+1);
Rotosym  r2(gLeds, gInterlaced, 1*kLedsPerStrip+1*(Icicle::kFullLength+Icicle::kInterSegmentGap)+1);
Rotosym  r3(gLeds, gInterlaced, 2*kLedsPerStrip+1);
Rotosym  r4(gLeds, gInterlaced, 3*kLedsPerStrip+1);
Rotosym  r5(gLeds, gInterlaced, 4*kLedsPerStrip+1);
Rotosym  r6(gLeds, gInterlaced, 5*kLedsPerStrip+1);
Rotosym  r7(gLeds, gInterlaced, 6*kLedsPerStrip+1);
Rotosym  r8(gLeds, gInterlaced, 7*kLedsPerStrip+1);

const int kBaubleCount = 9;
Bauble* gBaubles[kBaubleCount] = {
  &r1, &r2, &r3, &r4, &r5, &r6, &r7, &r8, &b1
};
#elif TEENSY_ID == 1
// The baubles
Icicle     b0(gLeds, gInterlaced, 5*kLedsPerStrip+1);
Icicle    b1(gLeds, gInterlaced, 5*kLedsPerStrip+1*(Icicle::kFullLength+Icicle::kInterSegmentGap)+1);
Icicle     b2(gLeds, gInterlaced, 5*kLedsPerStrip+2*(Icicle::kFullLength+Icicle::kInterSegmentGap)+1);
Icicle      b3(gLeds, gInterlaced, 7*kLedsPerStrip+1);
Icicle      b4(gLeds, gInterlaced, 4*kLedsPerStrip+1);
Star        b5(gLeds, gInterlaced, 0*kLedsPerStrip+1);
Bow         b6(gLeds, gInterlaced, 1*kLedsPerStrip+1);
Icicle      b7(gLeds, gInterlaced, 2*kLedsPerStrip+1);

const int kBaubleCount = 8;
Bauble* gBaubles[kBaubleCount] = {
  &b0, &b1, &b2, &b3, &b4, &b5, &b6, &b7
};
#elif TEENSY_ID == 2
// The baubles
Bow  b0(gLeds, gInterlaced, 0*kLedsPerStrip+1);
Slant b1(gLeds, gInterlaced, 1*kLedsPerStrip+1);
Triangle      b2(gLeds, gInterlaced, 2*kLedsPerStrip+1);
Tricorn      b3(gLeds, gInterlaced, 3*kLedsPerStrip+1);
Icicle b4(gLeds, gInterlaced, 4*kLedsPerStrip+1);
Reflect b5(gLeds, gInterlaced, 5*kLedsPerStrip+1);
Reflect b6(gLeds, gInterlaced, 6*kLedsPerStrip+1);
Chevron b7(gLeds, gInterlaced, 7*kLedsPerStrip+1);

const int kBaubleCount = 8;
Bauble* gBaubles[kBaubleCount] = {
  &b0, &b1, &b2, &b3, &b4, &b5, &b6, &b7
};
#elif TEENSY_ID == 3
// The baubles
Star     b0(gLeds, gInterlaced, 0*kLedsPerStrip+1);
Chevron  b1(gLeds, gInterlaced, 1*kLedsPerStrip+1);
Geostar b2(gLeds, gInterlaced, 2*kLedsPerStrip+1);
Chevron   b3(gLeds, gInterlaced, 3*kLedsPerStrip+1);
Geostar   b4(gLeds, gInterlaced, 4*kLedsPerStrip+1);
Geostar b5(gLeds, gInterlaced, 5*kLedsPerStrip+1);
Tricorn b6(gLeds, gInterlaced, 6*kLedsPerStrip+1);
Star b7(gLeds, gInterlaced, 7*kLedsPerStrip+1);

const int kBaubleCount = 8;
Bauble* gBaubles[kBaubleCount] = {
  &b0, &b1, &b2, &b3, &b4, &b5, &b6, &b7
};
#elif TEENSY_ID == 4
// The baubles
Star b0(gLeds, gInterlaced, 0*kLedsPerStrip+1);
Icicle   b1(gLeds, gInterlaced, 1*kLedsPerStrip+1);
Rotosym b2(gLeds, gInterlaced, 1*kLedsPerStrip+1*(Icicle::kFullLength+Icicle::kInterSegmentGap)+1);
Rotosym b3(gLeds, gInterlaced, 2*kLedsPerStrip+1);
Tricorn b4(gLeds, gInterlaced, 4*kLedsPerStrip+1);
Geostar b5(gLeds, gInterlaced, 5*kLedsPerStrip+1);
Slant b6(gLeds, gInterlaced, 7*kLedsPerStrip+1);
Icicle b7(gLeds, gInterlaced, 6*kLedsPerStrip+1);

const int kBaubleCount = 8;
Bauble* gBaubles[kBaubleCount] = {
  &b0, &b1, &b2, &b3, &b4, &b5, &b6, &b7
};
#endif

const int kTouchPin1 = 22;
const int kTouchPin2 = 23;

// Touch sensors
const int kTouchPadCount = 2;
TouchSensor gTouchPads[kTouchPadCount] = {
  TouchSensor(kTouchPin1),
  TouchSensor(kTouchPin2)
};
// Track whether we should send all touch readings to the controller
bool gStreamTouchPadReadings[kTouchPadCount] = {
  false, false
};

// Define this to just get debugging output rather than command comms
//#define PRINT

// Define this to have the touch sensors connected to *this* Teensy control the Baubles on this Teensy
//#define LOCAL_CONTROL


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Seed our random number generator with a tiny bit of entropy from the real world
  // which will be a *bit* better than having all Teensys seed their baubles identically
  randomSeed(analogRead(kTouchPin1));
  gLeds.begin();
  gLeds.show();
#ifdef PRINT
  Serial.println("Let's go!");
  Serial.print("Calibrating...");
#else
  ReportId();
#endif

  // Set initial bauble attract modes
  for (int m = 0; m < kBaubleCount; m++)
  {
    gBaubles[m]->chooseRandomAttractMode();
  }
#if 0
  //gBaubles[0]->setPattern(Bauble::eReachForTheStar);
  gBaubles[0]->setPattern(Bauble::eClimbing);
  gBaubles[1]->setPattern(Bauble::ePulse);
  gBaubles[2]->setPattern(Bauble::eFalling);
  gBaubles[3]->setPattern(Bauble::eInsideOut);
  gBaubles[4]->setPattern(Bauble::eClimbing);
  gBaubles[5]->setPattern(Bauble::eFalling);
  gBaubles[6]->setPattern(Bauble::eFalling);
  gBaubles[7]->setPattern(Bauble::eInsideOut);
#endif

  // Take initial calibration readings for each touch pad
  for (int i = 0; i < kTouchPadCount; i++)
  {
    gTouchPads[i].begin();
  }
}

int hueOffset = 0;

void loop() {
  if (millis() % 4000 < 100)
  {
    hueOffset = (hueOffset + 1) % 360;
  }

  // See if there's any news from the Raspberry Pi
  ProcessIncomingCommands();

  // Read in the current touch values
  for (int i = 0; i < kTouchPadCount; i++)
  {
    if (gTouchPads[i].takeReading() || gStreamTouchPadReadings[i])
    {
      // Report the event
      if (gTouchPads[i].touched())
      {
        ReportTouchDown(i, gTouchPads[i]);
      }
      else
      {
        ReportTouchRelease(i, gTouchPads[i]);
      }
    }
  }
#ifdef LOCAL_CONTROL
  gBaubles[0]->touched(gTouchPads[0].touched(), hueOffset);
  gBaubles[1]->touched(gTouchPads[1].touched(), hueOffset);
  gBaubles[2]->touched(gTouchPads[0].touched() && gTouchPads[1].touched(), hueOffset);
#endif
#if 0
  gBaubles[4]->touched(gTouchPads[2].touched(), hueOffset);
  gBaubles[6]->touched(gTouchPads[3].touched(), hueOffset);
  gBaubles[3]->touched(gTouchPads[1].touched() && gTouchPads[4].touched(), hueOffset);
  gBaubles[5]->touched(gTouchPads[1].touched() && gTouchPads[4].touched(), hueOffset);
  gBaubles[7]->touched(gTouchPads[0].touched() && gTouchPads[4].touched(), hueOffset);
#endif

  for (int m = 0; m < kBaubleCount; m++)
  {
    gBaubles[m]->tick(hueOffset);
  }
  gLeds.show();
  //delay(500);
}

