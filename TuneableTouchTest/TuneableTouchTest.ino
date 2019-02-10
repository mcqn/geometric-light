#include "FastLED.h"
#include "TouchSensor.h"

#define DATA_PIN    3
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
const int kLEDCount = 13;
CRGB gLEDs[kLEDCount];

const int kTouchPin = 22;
const int kLowerThresholdPot = A2;
const int kRangePot = A1;

const int kThresholdLowWatermark = 800;
const int kThresholdHighWatermark = 5000;
const int kRangeLowWatermark = 500;
const int kRangeHighWatermark = 5000;

// Touch sensors
TouchSensor gTouchPad(kTouchPin);

float filteredTouch = 800;
float fastFilter = 800;
float priorError = 1;
float K;

void kalmanFilter(float Z)
{
  float K = priorError / (priorError + 0.5);
  filteredTouch = filteredTouch + K * (Z - filteredTouch);
  priorError = (1 - K)* priorError;
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Let's go!");
  delay(1000);
  gTouchPad.begin();

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(gLEDs, kLEDCount).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(96);
}

void loop()
{
  // Work out the threshold values for the touch sensor
#if 0
  gTouchPad.iLowerThreshold = map(analogRead(kLowerThresholdPot), 0, 1023, kThresholdLowWatermark, kThresholdHighWatermark);
  gTouchPad.iUpperThreshold = gTouchPad.iLowerThreshold + map(analogRead(kRangePot), 0, 1023, kRangeLowWatermark, kRangeHighWatermark);
  if (gTouchPad.iLowerThreshold < 1000)
    Serial.print(" ");
  Serial.print(gTouchPad.iLowerThreshold);
  Serial.print(", ");
  if (gTouchPad.iUpperThreshold < 1000)
    Serial.print(" ");
  Serial.print(gTouchPad.iUpperThreshold);
  Serial.print(", ");
#endif

  // Read in the current touch value
  gTouchPad.takeReading();
  if (gTouchPad.iLastReading < 1000)
    Serial.print(" ");
  Serial.print(gTouchPad.iLastReading);
  Serial.print(", ");
  if (gTouchPad.touched())
  {
    Serial.print("800, ");
  }
  else
  {
    Serial.print("500, ");
  }

  Serial.print(gTouchPad.iLongFilter);
  Serial.print(", ");
  Serial.print(gTouchPad.iFastFilter);
  Serial.println();

#if 0
  // Show it on the LEDs
  int i = 0;
  while (i < map(constrain(gTouchPad.iLastReading, gTouchPad.iLowerThreshold, gTouchPad.iUpperThreshold), gTouchPad.iLowerThreshold, gTouchPad.iUpperThreshold, 0, kLEDCount))
  {
//Serial.print("#");
    gLEDs[i] = CHSV(50, 200, 255);
    i++;
  }
  while (i < kLEDCount)
  {
//Serial.print("_");
    gLEDs[i] = CHSV(200, 20, 100);
    i++;
  }
  if (fastFilter - filteredTouch > 150)
  {
    gLEDs[11] = CRGB::Blue;
  }
#endif
  if (gTouchPad.touched())
  {
    gLEDs[12] = CRGB::Red;
  }
//Serial.println();
  FastLED.show();

  delay(50);
}
