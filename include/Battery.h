#pragma once
#include "Config.h"
#include <Arduino.h>
#include "Devices.h"

void battery_init()
{
    pinMode(BATTERY_VOLTS, INPUT);
}

class Battery
{
private:
    float batteryVolts;
    const float batteryDividerRatio = 2.0f;

public:
    float getVolts()
    {
        return batteryVolts;                                                                    
    }
    
    void getBatteryVolts()
    {   
        int adcValue = analogRead(BATTERY_VOLTS);
        Serial.print(adcValue);
        Serial.print("  ");
        batteryVolts = adcValue * (5.0f * batteryDividerRatio / 1023.0f);
    }
};
