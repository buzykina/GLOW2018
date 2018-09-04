/*
  This example will transmit a universe via Art-Net into the Network.
  This example may be copied under the terms of the MIT license, see the LICENSE file for details
*/

// Local libraries/classes
#include "src/FlexSensor/FlexSensor.h"

#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArtnetWifi.h>

#define s_pl Serial.println
#define s_p Serial.print

//Wifi Settings
const char *ssid = "ASUS_50";
const char *password = "11183648";
// Artnet Settings
const int startUniverse = 1;         // CHANGE FOR YOUR SETUP most software this is 1, some software send out Artnet first universe as 0.
const char host[] = "192.168.1.60"; // CHANGE FOR YOUR SETUP your destination
// Flex sensor settings
const int FLEX_PIN = 34;                        // Pin connected to voltage divider output
//const unsigned long recalibrateMs = 10000000;    // Recalibrate the sensors every 10 seconds (in microseconds)
const int numFlexSensors = 16; // The number of flex sensors that are connected

ArtnetWifi Artnet; // Artnet settings
FlexSensor *flexSensors[numFlexSensors]; // Instantiate all flex sensors

// connect to wifi – returns true if successful or false if not
boolean ConnectWifi(void)
{
  boolean state = true;
  int i = 0;

  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    if (i > 20)
    {
      state = false;
      break;
    }
    i++;
  }
  if (state)
  {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.println("");
    Serial.println("Connection failed.");
  }

  return state;
}

float _averageMeasurements[16];
float alpha = 0.25;

void setup()
{
  Serial.begin(9600);
  pinMode(26, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(34, INPUT);

  for (int i = 0; i < numFlexSensors; ++i)
  {
    flexSensors[i] = new FlexSensor(i);
  }

  ConnectWifi();
  Artnet.begin(host);
  Artnet.setLength(numFlexSensors + 1);
  Artnet.setUniverse(startUniverse);
}

int oldMillis = 0;
void loop()
{
  int amountActive = 0;
  for (int i = 0; i < numFlexSensors; i++)
  {
    int value = flexSensors[i]->getByte();
    if (value)
    {
      amountActive++;
    }
    s_pl(value);
    Artnet.setByte(i, value);
  }
  if (amountActive >= 3)
  {
    Artnet.setByte(numFlexSensors, 255);
    s_pl("auw!");
  }
  else
  {
    Artnet.setByte(numFlexSensors, 0);
  }

  Artnet.write();
  delay(10);

  if ((millis() - oldMillis) > 1000)
  {
    for (int i = 0; i < numFlexSensors; i++) {
      //flexSensors[i].calibrate();
    }
    oldMillis = millis();
  }
}






