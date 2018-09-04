/*
  FlexSensor.cpp - Library for reading resistance of flex FlexSensor
*/

#include "Arduino.h"
#include "FlexSensor.h"
#include <MUX74HC4067.h>

#define s_pl Serial.println
#define s_p Serial.print

MUX74HC4067 Mux(26, 25, 33, 32, 35);

FlexSensor::FlexSensor(int id) {
	Mux.signalPin(34, INPUT, ANALOG);
	_identifier = id;
	calibrate();
	_midPointArrPos = 0;

	s_p("_identifier: ");
	s_pl(_identifier);
	for (int i = 0; i < 10; i++)
	{
		int16_t* a = new int16_t();
		*a = getAverage();
		s_p("getAverage(): ");
		s_pl(getAverage());
		_midPointArr[i] = a;
	}
}

/**
   Sets the multiplexer id for the flex sensor
 **/
void FlexSensor::setId(int id)
{
  _identifier = id;
}

/**
   Calibrate the sensor so that the current value is the midpoint
 **/

int FlexSensor::calibrate()
{
  _midPoint = getAverage();
  _averageMeasurement = _midPoint;
  return _midPoint;
}

/**
   Get a int  value from 0-255
 **/
int FlexSensor::getByte()
{
	updateMidpoint();
  // Get measured value, and compare to the midpoint value
  int value = abs(abs(_midPoint - getRaw()));

  // If the value is within the error margin, return 0
  if (value < _margin)
  {
    return 0;
  }
  else if (value > _range) { // If the value is out of the set limit (ie very high), return 255
    return 255;
  }
  else { // Else return a corrected value between 0-254
    float shiftedValue = ((float) value / (float)_range) * 255;
    return round(shiftedValue);
  }
}

/**
   Get Raw value from the flex sensor
 **/
float FlexSensor::getRaw()
{
  //int16_t data = Mux.read(_identifier);
  int16_t data = getAverage();

  _averageMeasurement = alpha * data + (1 - alpha) * _averageMeasurement; //exponential smoothing

  return _averageMeasurement;
}

int16_t FlexSensor::getAverage()
{
	int measurements = 0;
	int result = 0;
	for (int i = 0; i < _avgPasses; i++)
	{
		measurements += Mux.read(_identifier);
		delay(1);
	}
	result = measurements / _avgPasses;
	return result;
}

bool FlexSensor::isFlexed()
{
	int value = getRaw();
	int upperMargin = _midPoint + _margin;
	int lowerMargin = _midPoint - _margin;

	if (value > upperMargin || value < lowerMargin)
	{
		return true;
	}
	return false;
}

void FlexSensor::updateMidpoint()
{
	int16_t avg = getAverage();
	if (avg == 0)
	{
		return;
	}
	
	if (abs(avg - _midPoint) > _margin)
	{
		return;
	}

	*_midPointArr[_midPointArrPos] = avg;
	_midPointArrPos++;
	if (_midPointArrPos >= 10)
	{
		_midPointArrPos = 0;
	}

	int total = 0;
	for (int i = 0; i < 10; ++i)
	{
		total += *_midPointArr[i];
	}
	_midPoint = total / 10;
}






