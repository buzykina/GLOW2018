/*
  FlexSensor.h - Library for reading resistance of flex FlexSensor
  */
#ifndef FLEXSENSOR_H
#define FLEXSENSOR_H

#include "Arduino.h"
#include <MUX74HC4067.h>


class FlexSensor
{
private:
  int _identifier; // Identifier (0-15) for the flex sensor
  int16_t* _midPointArr[10];
  int _midPointArrPos;
  int16_t _midPoint;
  float _averageMeasurement = 2100;
  const int _avgPasses = 2; // Number of readings to get a accurate average
  const int _margin = 55;   // Margin in which the signal stays 0 (to allow for misreadings)
  const int _range = 75; // Working range of the flex Sensor
  const float alpha = 0.25; // Smoothing factor, lower is more smooth (and slower to react), recommended between 0.2 and 0.4
  void updateMidpoint();
  
public:
  void setId(int id); // Sets the multiplexer id
  int getByte(); // Get 0-255 value of the current flex sensor
  float getRaw(); // Get raw measurement from the flex sensor
  int16_t getAverage(); // Get raw measurement from the flex sensor
  bool isFlexed(); // Check if sensor is flexed
  int calibrate(); // Calibrates the flex sensor to the current angle
  FlexSensor(int id);
};

#endif
