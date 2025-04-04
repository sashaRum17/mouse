#pragma once
#include <Arduino.h>
#include "Config.h"
#include "Encoder.h"
#include "Battery.h"

void left_ISR();
void right_ISR();

EncoderConnectionParams left_ecp =
{
    .CLK_A_PIN = LEFT_CLOCK_A_PIN,
    .B_PIN = LEFT_B_PIN,
    .ENC_DIR = LEFT_ENC_DIR,
    .ISR_CALLBACK = left_ISR
};

EncoderConnectionParams right_ecp =
{
    .CLK_A_PIN = RIGHT_CLOCK_A_PIN,
    .B_PIN = RIGHT_B_PIN,
    .ENC_DIR = RIGHT_ENC_DIR,
    .ISR_CALLBACK = right_ISR
};

Encoder leftEncoder(&left_ecp);
Encoder rightEncoder(&right_ecp);

void left_ISR()
{
    leftEncoder.isr_callback();
}

void right_ISR()
{
    rightEncoder.isr_callback();
}

void init_asmr()
{
    
}

Battery volt;

#include "Motor.h"


