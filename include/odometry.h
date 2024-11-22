#include <Arduino.h>
#include "Config.h"
#include "Encoder.h"
#include "Devices.h"

float dSf = 0;
float dSr = 0;
float dSl = 0;
float x = 0;
float y = 0;
float d_teta = 0, teta = 0;
float L_phi_old;
float R_phi_old ;

void deltmath()
{
    dSl = (leftEncoder.q_phi - L_phi_old) * R;
    dSr = (rightEncoder.q_phi - R_phi_old) * R;
    dSf = (dSl + dSr) / 2;

    d_teta = (dSr - dSl) / WIDHT;
    teta += d_teta;


    L_phi_old = leftEncoder.q_phi;
    R_phi_old = rightEncoder.q_phi;
}

void coordinat()
{
    x += dSf * cos(teta);
    y += dSf * sin(teta);
}
