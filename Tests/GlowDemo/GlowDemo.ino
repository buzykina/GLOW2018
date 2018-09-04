#include <FastLED.h>

#define s_p Serial.print
#define s_pl Serial.println

#define DATAPIN 3
#define NUM_LEDS 65
#define POTPIN A0

CRGB strip[NUM_LEDS];
int led[2] = { 53, 63 };

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812, DATAPIN, RGB>(strip, NUM_LEDS);
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void red()
{
  strip[led[0]] = CRGB(255,0,0);
  strip[led[1]] = CRGB(255,0,0);
}

void green()
{
  strip[led[0]] = CRGB(0,255,0);
  strip[led[1]] = CRGB(0,255,0);
}

void neu()
{
  strip[led[0]] = CRGB(128,128,128);
  strip[led[1]] = CRGB(128,128,128);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0)
  {
    char in = Serial.read();
    if (in == '3')
    {
      red();
    }
    else if (in == '2')
    {
      green();
    }
    else if (in == '1')
    {
      neu();
    }
    else
    {
      s_pl("yo");
    }
    FastLED.show();
  }
}
