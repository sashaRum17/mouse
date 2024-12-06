#pragma once
#include "Config.h"
#include <Arduino.h>
#include "Devices.h"

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
        batteryVolts = adcValue * (5.0f * batteryDividerRatio / 1023.0f);
    }
};
