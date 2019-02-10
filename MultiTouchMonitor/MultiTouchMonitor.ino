#include "TouchSensor.h"

const int kTouchPin1 = 22;
const int kTouchPin2 = 23;
const int kTouchPin3 = 17;
const int kTouchPin4 = 18;
const int kTouchPin5 = 19;

// Touch sensors
const int kTouchPadCount = 5;
TouchSensor gTouchPads[kTouchPadCount] = {
  TouchSensor(kTouchPin1, 1000, 1800),
  TouchSensor(kTouchPin2, 1000, 2500),
  TouchSensor(kTouchPin3, 1400, 2800),
  TouchSensor(kTouchPin4,  900, 2100),
  TouchSensor(kTouchPin5, 1000, 1800)
};


void setup()
{
  Serial.begin(9600);
  Serial.println("Let's go!");
  for (int i = 0; i < kTouchPadCount; i++)
  {
    gTouchPads[i].setBaseline(1000);
    Serial.print(i);
    Serial.print(": ");
    Serial.print(gTouchPads[i].iLowerThreshold);
    Serial.print(" -> ");
    Serial.print(gTouchPads[i].iUpperThreshold);
    Serial.print(" ");
  }
  Serial.println();
}

void loop()
{
  // Read in the current touch values
  for (int i = 0; i < kTouchPadCount; i++)
  {
    gTouchPads[i].takeReading();
  }
  for (int j = 0; j < kTouchPadCount; j++)
  {
    if (gTouchPads[j].iLastReading < 1000)
      Serial.print(" ");
    Serial.print(gTouchPads[j].iLastReading);
    Serial.print(", ");
    if (gTouchPads[j].touched())
    {
      Serial.print("800, ");
    }
    else
    {
      Serial.print("500, ");
    }
  }
  Serial.println();
  delay(200);
}
