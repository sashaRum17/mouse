#include <Arduino.h>
#include "Encoder_left.h"
#include "Encoder_right.h"
#include "Config.h"
#include "VelEstimator.h"
#include "Devices.h"
#include "Encoder.h"


void setup(){
  ///////// INIT /////////
  Serial.begin(9600);
  leftEncoder.init();
  rightEncoder.init();
}

void loop()
{
  ///////// TIMER /////////
  // Задание постоянной частоты главного цикла прогааммы
  static uint32_t timer = micros();
  while(micros() - timer < Ts_us)
    ;
  timer = micros();
  
  ///////// SENSE /////////
  // Считывание датчиков
  leftEncoder.tick();
  rightEncoder.tick();
  
  // const float left_phi = g_left_phi;
  // const float right_phi = g_right_phi;
  // velest_tick();
  // const float left_w = g_left_w;
  // const float right_w = g_right_w;


  ///////// PLAN /////////
  // Расчет управляющих воздействий

  ///////// ACT /////////
  // Приведение управляющих воздействий в действие и логирование данных  
  Serial.print(leftEncoder.q_phi);
  Serial.print(" ");
  Serial.println(rightEncoder.q_phi);
}