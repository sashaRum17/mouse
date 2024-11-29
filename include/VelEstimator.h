
#pragma once
#include "Config.h"



float left_vel_estimator(float phi)
{
    // init
    static float phi_old = 0;

    //tick
    float w_raw = (phi-phi_old) / Ts_s;
    phi_old = phi;

    return w_raw;
}

float  left_low_pass_filter(float w_raw)
{
    //init
    static float w = 0;
    w += (w_raw - w)* LPF_ALPHA;

    return w;
}

float right_vel_estimator(float phi)
{
    // init
    static float phi_old = 0;

    //tick
    float w_raw = (phi-phi_old) / Ts_s;
    phi_old = phi;

    return w_raw;
    
}

float  right_low_pass_filter(float w_raw)
{
    //init
    static float w = 0;
    w += (w_raw - w)* LPF_ALPHA;

    return w;
}

float g_left_w = 0;
float g_right_w = 0;

void velest_tick()
{
    const float left_phi = leftEncoder.q_phi;
    const float right_phi = rightEncoder.q_phi;
    const float left_w_raw = left_vel_estimator(left_phi);
    const float right_w_raw = right_vel_estimator(right_phi);

    g_left_w = left_low_pass_filter(left_w_raw);
    g_right_w = right_low_pass_filter(right_w_raw);
}