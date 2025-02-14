#include <Arduino.h>

#include "Config.h"
#include "VelEstimator.h"
#include "Devices.h"
#include "Encoder.h"
#include "odometry.h"
#include "Battery.h"
#include "Motor.h"
#include "Switch.h"
#include "ASMR.h"

ASMR asmr;

void setup()
{
  ///////// INIT /////////
  Serial.begin(9600);

  leftEncoder.init();
  rightEncoder.init();

  asmr.addAction(FWD);
  asmr.addAction(STOP);
}

void loop()
{
  ///////// TIMER /////////
  // Задание постоянной частоты главного цикла прогааммы
  static uint32_t timer = micros();
  while (micros() - timer < Ts_us)
    ;
  timer = micros();

  ///////// SENSE /////////
  // Считывание датчиков
  leftEncoder.tick();
  rightEncoder.tick();

  ///////// PLAN /////////
  // Расчет управляющих воздействий
  coordinat();
  deltmath();
  decodeFunctionSwitch();
  volt.getBatteryVolts();

  ///////// ACT /////////
  // Приведение управляющих воздействий в действие и логирование данных
 asmr.exec();
}