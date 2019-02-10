// TouchSensor.h
// (c) Copyright 2017 MCQN Ltd.
//
// Class to encapsulate a touch sensor

#ifndef TOUCHSENSOR_H
#define TOUCHSENSOR_H

class TouchSensor
{
public:
  const float kLongFilterFactor = 0.9999;
  const int kDefaultTouchThreshold = 80;
public:
  TouchSensor(int aTouchPin) 
    : iTouchPin(aTouchPin), iTouchThreshold(kDefaultTouchThreshold)
      {};
  // Seed the sensor averages with initial readings
  void begin();
  // Set the threshold above which the touch sensor reports a "touch"
  void setThreshold(int aThreshold) { iTouchThreshold = aThreshold; };
  // Take a raw reading from the touch sensor
  int readRaw();
  // Take a reading and store it locally
  // Return whether or not the touch state changed (i.e. from untouched to touched, or touched to untouched)
  bool takeReading();
  // Return whether or not the touch sensor was being touched last time a reading was taken
  bool touched();
public:
  int iTouchPin;
  int iTouchThreshold;
  int iLastReading;
  float iLongFilter;
};

void TouchSensor::begin()
{
  // Do a tiny bit smoothing when we start up to counteract
  // any spikes on the signal
  iLongFilter = readRaw();
  for (int i = 0; i < 1000; i++)
  {
    iLongFilter = (iLongFilter*0.99)+(readRaw()*(1-0.99));
    delay(5);
  }
}

int TouchSensor::readRaw()
{
  // As the pressure sensor is the lower half of a voltage divider and its resistance
  // drops with pressure, the reading goes down when it's pressed, so invert the signal
  return 1023 - analogRead(iTouchPin);
}

bool TouchSensor::takeReading()
{
  bool wasTouched = touched();
  iLastReading = readRaw();
  iLongFilter = (iLongFilter*kLongFilterFactor)+(iLastReading*(1-kLongFilterFactor));
  // Return whether or not state changed
  return wasTouched != touched();
}

bool TouchSensor::touched()
{
  bool res = iLastReading > iLongFilter + iTouchThreshold;
  return res;
}

#endif
