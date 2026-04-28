#pragma once

// ─── Credenciales del Access Point ───────────────────────────────────────────
#define WIFI_SSID     "WallE-Control"
#define WIFI_PASSWORD "walle1234"

// ─── Configuración I2C ───────────────────────────────────────────────────────
#define I2C_SDA  21
#define I2C_SCL  22

// ─── Configuración PCA9685 ───────────────────────────────────────────────────
#define PWM_FREQ     50     // Frecuencia estándar para servos (Hz)
#define SERVO_CANAL  0      // Canal del PCA9685 donde está conectado el servo

// ─── Límites del servo ────────────────────────────────────────────────────────
#define POS_MIN    15
#define POS_MAX    70
#define VELOCIDAD  2
#define INTERVALO  20

// ─── Conversión de grados a pulso PWM ────────────────────────────────────────
// El PCA9685 trabaja con valores de pulso, no con grados directamente
// Estos valores son estándar para la mayoría de servos (ajustar si es necesario)
#define PULSO_MIN  205    // Corresponde a 1ms  (0°)
#define PULSO_MAX  410    // Corresponde a 2ms  (180°)