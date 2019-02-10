/*  OctoWS2811 BasicTest.ino - Basic RGB LED Test
    http://www.pjrc.com/teensy/td_libs_OctoWS2811.html
    Copyright (c) 2013 Paul Stoffregen, PJRC.COM, LLC

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

  Required Connections
  --------------------
    pin 2:  LED Strip #1    OctoWS2811 drives 8 LED Strips.
    pin 14: LED strip #2    All 8 are the same length.
    pin 7:  LED strip #3
    pin 8:  LED strip #4    A 100 ohm resistor should used
    pin 6:  LED strip #5    between each Teensy pin and the
    pin 20: LED strip #6    wire to the LED strip, to minimize
    pin 21: LED strip #7    high frequency ringining & noise.
    pin 5:  LED strip #8
    pin 15 & 16 - Connect together, but do not use
    pin 4 - Do not use
    pin 3 - Do not use as PWM.  Normal use is ok.

  This test is useful for checking if your LED strips work, and which
  color config (WS2811_RGB, WS2811_GRB, etc) they require.
*/

#include <OctoWS2811.h>

const int ledsPerStrip = 310;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

bool interlaced = false;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config, interlaced);

void setup() {
  leds.begin();
  leds.show();
}

#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00
#define PINK   0xFF1088
#define ORANGE 0xE05800
#define WHITE  0xFFFFFF

// Less intense...
/*
#define RED    0x160000
#define GREEN  0x001600
#define BLUE   0x000016
#define YELLOW 0x101400
#define PINK   0x120009
#define ORANGE 0x100400
#define WHITE  0x101010
*/

void loop() {
  int microsec = 2000000 / leds.numPixels();  // change them all in 2 seconds

// Icicle
  for (int n = 0; n < 61; n+=(1+interlaced))
  {
    leds.setPixel(1+interlaced+n, 0x0000ff);
  }
// Triangle
// Kazimier
// Rotosym
// Bow
#if 0
// Reflect
  for (int n = 0; n < 113; n+=(1+interlaced))
  {
    leds.setPixel(1+interlaced+n, 0x0000ff);
  }
  for (int j = 0; j < 44; j+=(1+interlaced))
  {
    leds.setPixel(115+interlaced+j, 0x991111);
    leds.setPixel(264+interlaced+j, 0x991111);
  }
  for (int m = 0; m < 31; m+=(1+interlaced))
  {
    leds.setPixel(160+interlaced+m, 0x119911);
    leds.setPixel(232+interlaced+m, 0x119911);
  }
  for (int p = 0; p < 18; p+=(1+interlaced))
  {
    leds.setPixel(193+interlaced+p, 0x111199);
    leds.setPixel(213+interlaced+p, 0x111199);
  }
// Tricorn
  for (int k = 0; k < 3; k++)
  {
    for (int j = 0; j < 28; j+=(1+interlaced))
    {
      leds.setPixel((101*k)+1+interlaced+j, 0x991111);
      leds.setPixel((101*k)+72+interlaced+j, 0x119911);
    }
    for (int m = 0; m < 39; m+=(1+interlaced))
    {
      leds.setPixel((101*k)+31+interlaced+m, 0x111199);
    }
  }
// chevron
  for (int j = 0; j < 37; j+=(1+interlaced))
  {
    leds.setPixel(1+interlaced+j, 0x991111);
    leds.setPixel(40+interlaced+j, 0x119911);
    leds.setPixel(79+interlaced+j, 0x111199);
    leds.setPixel(118+interlaced+j, 0xff6600);
    leds.setPixel(157+interlaced+j, 0x00ff66);
    leds.setPixel(196+interlaced+j, 0x6600ff);
  }
  // slant
  for (int j = 0; j < 49; j+=(1+interlaced))
  {
    leds.setPixel(1+interlaced+j, 0x991111);
    leds.setPixel(52+interlaced+j, 0x119911);
    leds.setPixel(103+interlaced+j, 0x111199);
  }
#endif
  unsigned long s = millis();
  while (millis() - s < 15000)
  {
    leds.show();
  }

  for (int i = 0; i < ledsPerStrip; i++)
  {
    Serial.println(i);
    leds.setPixel(i, 0xff3300);
    s = millis();
    while (millis() - s < 800)
    {
      leds.show();
    }
    leds.setPixel(i, 0);
  }
  // uncomment for voltage controlled speed
  // millisec = analogRead(A9) / 40;

  colorWipe(RED, microsec);
  colorWipe(GREEN, microsec);
  colorWipe(BLUE, microsec);
  colorWipe(YELLOW, microsec);
  colorWipe(PINK, microsec);
  colorWipe(ORANGE, microsec);
  colorWipe(WHITE, microsec);
  colorWipe(0, microsec);
}

void colorWipe(int color, int wait)
{
  for (int i=0; i < leds.numPixels(); i++) {
    leds.setPixel(i, color);
    leds.show();
    delayMicroseconds(wait);
  }
}
