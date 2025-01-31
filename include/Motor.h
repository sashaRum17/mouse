#pragma once
#include <Arduino.h>
#include "Config.h"
#include "Devices.h"
#include "VelEstimator.h"

void drive_left(float u)
{
    volt.getBatteryVolts();
    float Volts = volt.getVolts();

    float pwm = (255.0 * (u / Volts));

    pwm = constrain(pwm, -255, 255);

    if (pwm >= 0)
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

    float pwm = (255.0 * (u / Volts));

    pwm = constrain(pwm, -255, 255);

    if (pwm >= 0)
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

void drive_math_left(int w0)
{
    float dI, u;
    float e = w0 - g_left_w;
    static float I = 0;

    float kP = k1;
    float P = kP * e;
    float T1 = Tm;
    if (u == constrain(u, -max_output, max_output) || (e * u) < 0)
    {
        float kI = k1 / T1;
        dI = e * kI;
        I += dI;
    }
    u = P + I;

    drive_left(u);
}

void drive_math_right(int w0)
{
    float dI, u;
    float e = w0 - g_right_w;

    float kP = k1;
    float P = kP * e;
    float T1 = Tm;

    static float I = 0;
    if (u == constrain(u, -max_output, max_output) || (e * u) < 0)
    {
        float kI = k1 / T1;
        dI = e * Ts_s;
        I += dI;
    }
    u = P + I;
    drive_right(u);
}

void w_drive(float forwardVel, float headingVel)
{
    float vf0 = forwardVel / WHEEL_RADIUS;
    const float deltW = headingVel * HEADING_VEL_TO_DELTA_W;

    float gLeftW = vf0 - deltW;
    float gRightW = vf0 + deltW;

    drive_math_left(gLeftW);
    drive_math_right(gRightW);
    Serial.print(vf0);
    Serial.print(";  ");
    Serial.print(deltW);
    Serial.print(";  ");
    Serial.print(gLeftW);
    Serial.print(";  ");
    Serial.println(gRightW);
}