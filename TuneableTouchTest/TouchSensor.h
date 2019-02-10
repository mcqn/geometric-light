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
  const float kFastFilterFactor = 0.6;
  const int kTouchThreshold = 130;
public:
  TouchSensor(int aTouchPin) 
    : iTouchPin(aTouchPin) {};
  // Seed the sensor averages with initial readings
  void begin();
  // Take a raw reading from the touch sensor
  int readRaw();
  // Take a reading and store it locally
  void takeReading();
  // Return whether or not the touch sensor was being touched last time a reading was taken
  bool touched();
public:
  int iTouchPin;
  int iLastReading;
  float iLongFilter;
  float iFastFilter;
};

void TouchSensor::begin()
{
  // Do a tiny bit smoothing when we start up to counteract
  // any spikes on the signal
  iFastFilter = readRaw();
  for (int i = 0; i < 8000; i++)
  {
    iFastFilter = (iFastFilter*kFastFilterFactor)+(readRaw()*(1-kFastFilterFactor));
    delay(5);
  }
  iLongFilter = iFastFilter;
}

int TouchSensor::readRaw()
{
  return touchRead(iTouchPin);  
}

void TouchSensor::takeReading()
{
  int newReading = readRaw();
  // The 240A power supply is really noisy and has regular spikes
  // so ignore really high readings
  if (newReading < iLastReading * 1.5)
  {
    iLastReading = newReading;
    iLongFilter = (iLongFilter*kLongFilterFactor)+(iLastReading*(1-kLongFilterFactor));
    iFastFilter = (iFastFilter*kFastFilterFactor)+(iLastReading*(1-kFastFilterFactor));
  }
  iLastReading = newReading;
}

bool TouchSensor::touched()
{
  return iFastFilter > iLongFilter + kTouchThreshold;
}

#endif
