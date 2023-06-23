# AirQualityMeter
###### University project - ESP32-based air quality sensor with e-paper display
## Description
Repository contains the code controlling the microcontroller system I had to build for an Microprocessor and Embedded Systems sybject on a university. Its main purpose is to measure volatile organic compounds and carbon dioxide equivalent. It consists of main 3 electronic parts:
* Ai-Thinker ESP-C3-32S-Kit
* 2.66inch 3-color E-Paper E-Ink Display Module
* SGP30 Multi-gas (VOC and CO₂eq) sensor Module

The microcontroller wakes up, lets the sensor warm up for 30 seconds and measures current air condition. Next, display driver prepares an image containing the measurement result and displays it on the display. After that, microcontroller enters deep sleep mode, sleeps for 5 minutes and the cycle gets repeated.

All the elements were soldered on a prototype board, which was a mandatory step in the project.

## Photo
![Photo](https://github.com/wm1511/AirQualityMeter/assets/72276813/edf96281-85de-49f4-b381-024adf949f94)
