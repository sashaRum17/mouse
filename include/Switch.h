#pragma once
#include <Arduino.h>
#include "Config.h"

uint32_t updateTime;
uint32_t updateInterval = 100; // in milliseconds

int decodeFunctionSwitch()
{
  int functionValue = analogRead(FUNCTION_SELECT);
  const int adcReading[] = {660, 647, 630, 614, 590, 570, 545, 522, 461,
                            429, 385, 343, 271, 212, 128, 44, 0};

  if (functionValue > 1000)
  {
    return 16; // pushbutton closed
  }
  int result = 16;
  for (int i = 0; i < 16; i++)
  {
    if (functionValue > (adcReading[i] + adcReading[i + 1]) / 2)
    {
      result = i;
      break;
    }
  }
  return result;
}

void switch_init()
{
  pinMode(FUNCTION_SELECT, INPUT);
}

