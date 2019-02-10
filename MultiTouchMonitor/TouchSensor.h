// TouchSensor.h
// (c) Copyright 2017 MCQN Ltd.
//
// Class to encapsulate a touch sensor

#ifndef TOUCHSENSOR_H
#define TOUCHSENSOR_H

class TouchSensor
{
public:
  TouchSensor(int aTouchPin, int aLowerThreshold, int aUpperThreshold) 
    : iTouchPin(aTouchPin), iLowerThreshold(aLowerThreshold), iUpperThreshold(aUpperThreshold) {};
  // Spend aPeriod milliseconds getting a baseline reading
  void setBaseline(unsigned long aPeriod);
  // Set the upper reading threshold
  void setUpperLimit(int aThreshold) { iUpperThreshold = aThreshold; };
  // Take a raw reading from the touch sensor
  int readRaw();
  // Take a reading, mapped proportionally between aLowerRange and aUpperRange
  int readMapped(int aLowerRange, int aUpperRange);
  // Take a reading and store it locally
  void takeReading();
  // Return last reading, mapped proportionally between aLowerRange and aUpperRange
  int getMapped(int aLowerRange, int aUpperRange);
  // Return whether or not the touch sensor was being touched last time a reading was taken
  bool touched();
public:
  int iTouchPin;
  int iLowerThreshold;
  int iUpperThreshold;
  int iLastReading;
};

void TouchSensor::setBaseline(unsigned long aPeriod)
{
  unsigned long start = millis();
  float rollingAv = touchRead(iTouchPin);
  readRaw();
  readRaw();
  while (millis() < start+aPeriod)
  {
    rollingAv = rollingAv*0.999 + (readRaw()*0.001);
    delay(100);
  }
  iLowerThreshold = rollingAv;
  iUpperThreshold = rollingAv*1.3;
}

int TouchSensor::readRaw()
{
  return touchRead(iTouchPin);  
}

int TouchSensor::readMapped(int aLowerRange, int aUpperRange)
{
  return map(constrain(readRaw(), iLowerThreshold, iUpperThreshold), iLowerThreshold, iUpperThreshold, aLowerRange, aUpperRange);
}

void TouchSensor::takeReading()
{
  iLastReading = readRaw();
}

int TouchSensor::getMapped(int aLowerRange, int aUpperRange)
{
  return map(constrain(iLastReading, iLowerThreshold, iUpperThreshold), iLowerThreshold, iUpperThreshold, aLowerRange, aUpperRange);
}

bool TouchSensor::touched()
{
  return iLastReading > iLowerThreshold + (iUpperThreshold-iLowerThreshold)*0.5;
}

#endif
