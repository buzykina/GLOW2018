# Glow2018Delta
This is the glow Delta project Git.

## Project Setup
In the arduino IDE install the following libraries:
- [https://github.com/rstephan/ArtnetWifi](ArtNetWifi)

Add the contents of MUX74HC4067.zip with the arduino IDE (add zip libraries) or extract them manually to your arduino libraries folder. For windows users:
``C:\Users\Username\Documents\Arduino\libraries``

## Code
The project runs on two ESP32's; One for sending the sensor data, and one to control the led grid. Each pair of esp32's controls 16 sets of leds, fibers and flex sensors.

## Proces, concepting & documentation
To see the proces, all of the testing and concepting, see this [google drive folder](https://drive.google.com/drive/u/0/folders/1zGHsh_xgOt1kellyIgeFcKTAbO9ZmK-l)