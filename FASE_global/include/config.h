#pragma once

// ─── Credenciales del Access Point ───────────────────────────────────────────
#define WIFI_SSID     "WallE-Control"
#define WIFI_PASSWORD "walle1234"

// ─── Configuración PCA9685 ───────────────────────────────────────────────────
#define PWM_FREQ   50
#define SERVOMIN   130
#define SERVOMAX   500

// ─── Velocidad de movimiento (ms entre cada grado) ───────────────────────────
#define VELOCIDAD  20

// ─── Canales PCA9685 ─────────────────────────────────────────────────────────
#define CANAL_CUELLO      11
#define CANAL_CEJA_DER    12
#define CANAL_CEJA_IZQ    13
#define CANAL_OJO_DER     14
#define CANAL_OJO_IZQ     15
#define CANAL_BRAZO_DER    0
#define CANAL_BRAZO_IZQ    1

// ─── Límites ceja izquierda ───────────────────────────────────────────────────
#define CEJA_IZQ_MIN   0
#define CEJA_IZQ_MAX   42

// ─── Límites ceja derecha ─────────────────────────────────────────────────────
#define CEJA_DER_MIN   0
#define CEJA_DER_MAX   42

// ─── Límites ojos ─────────────────────────────────────────────────────────────
#define OJO_IZQ_MIN    0
#define OJO_IZQ_MAX    40
#define OJO_DER_MIN    0
#define OJO_DER_MAX    40

// ─── Límites cuello ───────────────────────────────────────────────────────────
#define CUELLO_MIN     0
#define CUELLO_MAX     180
#define CUELLO_CENTRO  90

// ─── Límites brazos ───────────────────────────────────────────────────────────
#define BRAZO_IZQ_MIN   0
#define BRAZO_IZQ_MAX   112
#define BRAZO_DER_MIN   0
#define BRAZO_DER_MAX   112