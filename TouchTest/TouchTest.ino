#include <OctoWS2811.h>

const int kTouchPin = 23;

const int kPulsePin = A3;

// Thresholds used to map readings to colourspace
// gTouchLowerThreshold is calculated from background capacitance at boot
int gTouchLowerThreshold = 0;
const int kTouchUpperThreshold = 2800;

const int kLedsPerStrip = 300;

DMAMEM int gDisplayMemory[kLedsPerStrip*6];
int gDrawingMemory[kLedsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 gLeds(kLedsPerStrip, gDisplayMemory, gDrawingMemory, config);

#define PRINT

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  gLeds.begin();
  gLeds.show();
#ifdef PRINT
  Serial.println("Let's go!");
  Serial.print("Calibrating...");
#endif

  // Spend ten seconds 
  unsigned long start = millis();
  float rollingAv = touchRead(kTouchPin);
  while (millis() < start+5*1000UL)
  {
    rollingAv = rollingAv*0.999 + (touchRead(kTouchPin)*0.001);
    delay(100);
  }
  gTouchLowerThreshold = rollingAv;
#ifdef PRINT
  Serial.println("done.");
  Serial.print("Calibrated to ");
  Serial.println(gTouchLowerThreshold);
#endif
}

int gLedIdx = kLedsPerStrip;
int reading =0;

//#define PULSE

const int kPulseLowerThreshold = 450;
const int kPulseHigherThreshold = 550;

bool toggle = false;
int hueOffset = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() % 4000 < 100)
  {
    hueOffset = (hueOffset + 1) % 360;
  }

#ifdef PULSE
  int pulse = analogRead(kPulsePin);
  Serial.println(pulse);
  pulse = constrain(pulse, kPulseLowerThreshold, kPulseHigherThreshold);
  int hue = map(pulse, kPulseLowerThreshold, kPulseHigherThreshold, 0, 360);
  delay(10);
#else
  int reading = touchRead(kTouchPin);
#ifdef PRINT
  Serial.print(reading);
#endif
  reading = constrain(reading, gTouchLowerThreshold, kTouchUpperThreshold);
  // Hue is a value between 0 and 360
  int hue = map(reading, gTouchLowerThreshold, kTouchUpperThreshold, 0, 360);
#endif
#ifdef PRINT
  Serial.print(", ");
  Serial.print(reading);
  Serial.print(", ");
  Serial.print(hue);
  Serial.print(", ");
  Serial.print(gLedIdx);
  // Map HSV to RGB
  Serial.print(" - ");
  Serial.println(makeColor(hue, 100, 50), HEX);
  hue = (hue + hueOffset) % 360;
#endif
  // Shuffle all the LEDs along one
  for (int i = kLedsPerStrip; i > 0; i--)
  {
    int idx = i+2*kLedsPerStrip;
    gLeds.setPixel(idx, gLeds.getPixel(idx-1));
  }
  if (toggle)
  {
    gLeds.setPixel(0+2*kLedsPerStrip, 0);
  }
  else
  {
    gLeds.setPixel(0+2*kLedsPerStrip, makeColor(hue, 100, 50));
  }
  toggle = !toggle;
  gLeds.show();
  gLedIdx--;
  if (gLedIdx < 0)
  {
    gLedIdx = kLedsPerStrip;
  }
  //delay(300);
}

// Convert HSL (Hue, Saturation, Lightness) to RGB (Red, Green, Blue)
//
//   hue:        0 to 359 - position on the color wheel, 0=red, 60=orange,
//                            120=yellow, 180=green, 240=blue, 300=violet
//
//   saturation: 0 to 100 - how bright or dull the color, 100=full, 0=gray
//
//   lightness:  0 to 100 - how light the color is, 100=white, 50=color, 0=black
//
int makeColor(unsigned int hue, unsigned int saturation, unsigned int lightness)
{
  unsigned int red, green, blue;
  unsigned int var1, var2;

  if (hue > 359) hue = hue % 360;
  if (saturation > 100) saturation = 100;
  if (lightness > 100) lightness = 100;

  // algorithm from: http://www.easyrgb.com/index.php?X=MATH&H=19#text19
  if (saturation == 0) {
    red = green = blue = lightness * 255 / 100;
  } else {
    if (lightness < 50) {
      var2 = lightness * (100 + saturation);
    } else {
      var2 = ((lightness + saturation) * 100) - (saturation * lightness);
    }
    var1 = lightness * 200 - var2;
    red = h2rgb(var1, var2, (hue < 240) ? hue + 120 : hue - 240) * 255 / 600000;
    green = h2rgb(var1, var2, hue) * 255 / 600000;
    blue = h2rgb(var1, var2, (hue >= 120) ? hue - 120 : hue + 240) * 255 / 600000;
  }
  return (red << 16) | (green << 8) | blue;
}

unsigned int h2rgb(unsigned int v1, unsigned int v2, unsigned int hue)
{
  if (hue < 60) return v1 * 60 + (v2 - v1) * hue;
  if (hue < 180) return v2 * 60;
  if (hue < 240) return v1 * 60 + (v2 - v1) * (240 - hue);
  return v1 * 60;
}

