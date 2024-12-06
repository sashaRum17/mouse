//TIME
#define Ts_us 20000 // Период квантования в [мкс]
#define Ts_s (Ts_us / 1000000.0) // Период квантования в [с]

//MOTOR PARAMS
#define LEFT_CLOCK_A_PIN 2
#define LEFT_B_PIN 4
#define LEFT_ENC_DIR -1 // отриц направление -1

#define RIGHT_CLOCK_A_PIN 3
#define RIGHT_B_PIN 5
#define RIGHT_ENC_DIR 1 // отриц направление -1

#define ENC_PPR 48 // тиков на оборот энкодера
#define GEAR_RATIO 30

#define tick_to_rad (2.0 * M_PI / (ENC_PPR * GEAR_RATIO))
#define LPF_ALPHA (0.5)

#define R 0.016
#define WIDHT 0.07

#define BATTERY_VOLTS A7

#define LEFT_DIR 7
#define LEFT_PWM 9
#define RIGHT_DIR 8
#define RIGHT_PWM 10
#define LEFT_MOTOR_POLARITY 1
#define RIGHT_MOTOR_POLARITY 0
#define FUNCTION_SELECT 6


