#pragma once
#include <Arduino.h>
#include "Config.h"
#include "Devices.h"

void drive_left(float u)
{
    volt.getBatteryVolts();
    float Volts = volt.getVolts();
    int pwm = 255.0 * (u / Volts);
    pwm = constrain(pwm, -255, 255);

    if(pwm >= 0)
    {
        digitalWrite(LEFT_DIR, LEFT_MOTOR_POLARITY);
        analogWrite(LEFT_PWM, pwm);
    }
    else
    {
        digitalWrite(LEFT_DIR, !LEFT_MOTOR_POLARITY);
        analogWrite(LEFT_PWM, -pwm);
    }

}

void drive_right(float u)
{
    volt.getBatteryVolts();
    float Volts = volt.getVolts();
    int pwm = 255.0 * (u / Volts);
    pwm = constrain(pwm, -255, 255);

    if(pwm >= 0)
    {
        digitalWrite(RIGHT_DIR, RIGHT_MOTOR_POLARITY);
        analogWrite(RIGHT_PWM, pwm);
    }
    else
    {
        digitalWrite(RIGHT_DIR, !RIGHT_MOTOR_POLARITY);
        analogWrite(RIGHT_PWM, -pwm);
    }

}