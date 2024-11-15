#define ENC_PPR 48 // тиков на оборот энкодера
#define GEAR_RATIO 30

#define Ts_us 20000 // Период квантования в [мкс]
#define Ts_s (Ts_us / 1000000.0) // Период квантования в [с]

#define tick_to_rad (2.0 * M_PI / (ENC_PPR * GEAR_RATIO))

#define LPF_ALPHA (2*Ts_s)