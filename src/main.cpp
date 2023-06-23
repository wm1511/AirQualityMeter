#include "Adafruit_SGP30.h"
#include <GxEPD2_3C.h>
#include "imagedata.h"
#include "epdpaint.h"

GxEPD2_3C<GxEPD2_266c, GxEPD2_266c::HEIGHT> display(GxEPD2_266c(7, 21, 20, 10));
Adafruit_SGP30 sgp;

#define HEIGHT 296
#define WIDTH 152
#define COLORED 0
#define UNCOLORED 1

constexpr int32_t SIZE = HEIGHT * WIDTH / 8;
uint8_t blackImage[SIZE];
uint8_t redImage[SIZE];

void drawBackground(uint16_t TVOC, uint16_t eCO2) 
{
  if (TVOC < 50 || eCO2 < 500)
    memcpy(blackImage, gImage_good, SIZE);

  if (TVOC >= 50 && TVOC < 750)
    memcpy(blackImage, gImage_mediocre, SIZE);

  if (eCO2 >= 500 && eCO2 < 1000)
    memcpy(blackImage, gImage_mediocre, SIZE);

  if (TVOC >= 750 && TVOC < 6000)
    memcpy(blackImage, gImage_bad, SIZE);

  if (eCO2 >= 1000 && eCO2 < 2500)
    memcpy(blackImage, gImage_bad, SIZE);

  if (TVOC >= 6000 || eCO2 >= 2500)
    memcpy(blackImage, gImage_harmful, SIZE);
}

void drawTVOC(Paint& black, Paint& red, uint16_t TVOC)
{
  if (TVOC < 50)
  {
    black.DrawCircle(102, 48, 30, COLORED);
    black.DrawStringAt(86, 38, String(TVOC).c_str(), &Font24, COLORED);
  }
  else if (TVOC >= 50 && TVOC < 750)
  {
    red.DrawCircle(102, 48, 30, COLORED);
    black.DrawStringAt(78, 38, String(TVOC).c_str(), &Font24, COLORED);
  }
  else if (TVOC >= 750 && TVOC < 6000)
  {
    red.DrawCircle(102, 48, 30, COLORED);
    red.DrawStringAt(76, 40, String(TVOC).c_str(), &Font20, COLORED);
  }
  else
  {
    red.DrawFilledCircle(102, 48, 30, COLORED);
    red.DrawStringAt(76, 40, String(TVOC).c_str(), &Font20, UNCOLORED);
  }
}

void draweCO2(Paint& black, Paint& red, uint16_t eCO2)
{
  if (eCO2 < 500)
  {
    black.DrawCircle(40, 148, 30, COLORED);
    black.DrawStringAt(16, 140, String(eCO2).c_str(), &Font24, COLORED);
  }
  else if (eCO2 >= 500 && eCO2 < 1000)
  {
    red.DrawCircle(40, 148, 30, COLORED);
    black.DrawStringAt(16, 140, String(eCO2).c_str(), &Font24, COLORED);
  }
  else if (eCO2 >= 1000 && eCO2 < 2500)
  {
    red.DrawCircle(40, 148, 30, COLORED);
    red.DrawStringAt(14, 140, String(eCO2).c_str(), &Font20, COLORED);
  }
  else
  {
    red.DrawFilledCircle(40, 148, 30, COLORED);
    red.DrawStringAt(14, 140, String(eCO2).c_str(), &Font20, UNCOLORED);
  }
}

void setup() 
{
  while (!sgp.begin()) 
  {
    delay(100);
  }

  display.init(115200);
}

void loop() 
{  
  display.clearScreen();
  for (uint8_t i = 0; i < 10; ++i)
  {
    sgp.IAQmeasure();
    delay(3000);
  }
  while(!sgp.IAQmeasure()) {delay(200);}
 
  Paint redPaint(redImage, WIDTH, HEIGHT);
  Paint blackPaint(blackImage, WIDTH, HEIGHT);
  redPaint.Clear(UNCOLORED);

  drawBackground(sgp.TVOC, sgp.eCO2);
  draweCO2(blackPaint, redPaint, sgp.eCO2);
  drawTVOC(blackPaint, redPaint, sgp.TVOC);

  display.drawImage(blackImage, redImage, 0, 0, WIDTH, HEIGHT);

  display.hibernate();
  esp_deep_sleep(300000000);
}