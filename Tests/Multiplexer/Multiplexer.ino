/**
 * This example demonstrates how to read analog signals
 * It assumes there are potentiometers connected
 * to the 16 channels of the 74HC4067 mux/demux
 * 
 * For more about the interface of the library go to
 * https://github.com/pAIgn10/MUX74HC4067
 */

#include "MUX74HC4067.h"

// Creates a MUX74HC4067 instance
// 1st argument is the Arduino PIN to which the EN pin connects
// 2nd-5th arguments are the Arduino PINs to which the S0-S3 pins connect
MUX74HC4067 mux(26, 25, 33, 32, 35);
float _averageMeasurements[16];
float alpha = 0.25;

/*int readings[5]; // the readings from the analog input
int readIndex = 0; // the index of the current reading
int total = 0;     // the running total
int average = 0;   // the average
*/
void setup()
{
  Serial.begin(115200); // Initializes serial port
  // Waits for serial port to connect. Needed for Leonardo only
  while (!Serial)
    ;
  for (byte i = 0; i < 16; ++i)
  {
    _averageMeasurements[i] = mux.read(i);
    delay(10);
  }
  // Configures how the SIG pin will be interfaced
  // e.g. The SIG pin connects to PIN A0 on the Arduino,
  //      and PIN A0 is a analog input
  mux.signalPin(34, INPUT, ANALOG);
}

// Reads the 16 channels and reports on the serial monitor
// the corresponding value read by the A/D converter
void loop()
{
  int16_t data;

  for (byte i = 0; i < 16; ++i)
  {
    data = mux.read(5);
    _averageMeasurements[i] = alpha * data + (1 - alpha) * _averageMeasurements[i]; //exponential smoothing

    //Serial.print("Channel ");
    Serial.print(_averageMeasurements[i]);
    Serial.print(",");
  }

  Serial.println();
  //Serial.println(mux.read(5));

  delay(3);
}
