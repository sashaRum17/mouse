#pragma once

#include <Arduino.h>
#include "Config.h"


struct EncoderConnectionParams
{
    int CLK_A_PIN;
    int B_PIN;
    int ENC_DIR;
    void (*ISR_CALLBACK)();
};

class Encoder : public EncoderConnectionParams
{
private:
    int8_t ETT[4][4] = {0};
    volatile int counter = 0;
    volatile int8_t enc_old = 0;
    float phi = 0;

public:
    float &q_phi = phi;

    Encoder(EncoderConnectionParams *ecp) : EncoderConnectionParams(*ecp) {}

    void init()
    {
        pinMode(CLK_A_PIN, INPUT);
        pinMode(B_PIN, INPUT);

        noInterrupts();
        attachInterrupt(digitalPinToInterrupt(CLK_A_PIN), ISR_CALLBACK, CHANGE);

        ETT[0b00][0b01] = ENC_DIR;
        ETT[0b01][0b11] = ENC_DIR;
        ETT[0b11][0b10] = ENC_DIR;
        ETT[0b10][0b00] = ENC_DIR;

        ETT[0b00][0b10] = -ENC_DIR;
        ETT[0b10][0b11] = -ENC_DIR;
        ETT[0b11][0b01] = -ENC_DIR;
        ETT[0b01][0b00] = -ENC_DIR;

        interrupts();
    }

    void isr_callback()
    {
        const uint8_t B = digitalRead(B_PIN);
        // 0000000B
        const uint8_t CLK_A = digitalRead(CLK_A_PIN);
        const uint8_t A = CLK_A ^ B;
        // 0000000B
        const uint8_t enc = (A << 1) | B;
        /*
        000000AB = (0000000A << 1) | 0000000B;
        */

        counter += ETT[enc_old][enc];
        enc_old = enc;
    }

    void tick()
    {
        noInterrupts();
        const int counter_inc = counter;
        counter = 0;
        interrupts();

        phi += counter_inc * tick_to_rad;
    }

    void left_enc_tick() {}
};