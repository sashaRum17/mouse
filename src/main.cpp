#include <Arduino.h>
#include "Encoder_left.h"
#include "Encoder_right.h"
#include "Config.h"
#include "VelEstimator.h"


void setup(){
  ///////// INIT /////////
  Serial.begin(9600);
  left_enc_init();
  right_enc_init();
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
  left_enc_tick();
  right_enc_tick();
  const float left_phi = g_left_phi;
  const float right_phi = g_right_phi;
  velest_tick();
  const float left_w = g_left_w;
  const float right_w = g_right_w;
  ///////// PLAN /////////
  // Расчет управляющих воздействий

  ///////// ACT /////////
  // Приведение управляющих воздействий в действие и логирование данных  
  Serial.print(left_phi);
  
  Serial.println(right_phi);
}