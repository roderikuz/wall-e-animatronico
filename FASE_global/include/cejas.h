#pragma once
#include <Adafruit_PWMServoDriver.h>
#include "config.h"

// ─── Convierte grados a pulso ─────────────────────────────────────────────────
inline int gradosAPulsoCeja(int grados) {
  return map(grados, 0, 180, SERVOMIN, SERVOMAX);
}

// ─── Ceja izquierda: sube hasta máximo y regresa al reposo ───────────────────
inline void ciclocejaIzq(Adafruit_PWMServoDriver& pca) {
  // Subir
  for (int i = CEJA_IZQ_MIN; i <= CEJA_IZQ_MAX; i++) {
    pca.setPWM(CANAL_CEJA_IZQ, 0, gradosAPulsoCeja(i));
    delay(VELOCIDAD);
  }
  // Bajar
  for (int i = CEJA_IZQ_MAX; i >= CEJA_IZQ_MIN; i--) {
    pca.setPWM(CANAL_CEJA_IZQ, 0, gradosAPulsoCeja(i));
    delay(VELOCIDAD);
  }
}

// ─── Ceja derecha: sube hasta máximo y regresa al reposo ─────────────────────
// El servo está montado invertido por eso los grados van de MAX a MIN
inline void cicloCejaDer(Adafruit_PWMServoDriver& pca) {
  // Subir (invertido)
  for (int i = CEJA_DER_MAX; i >= CEJA_DER_MIN; i--) {
    pca.setPWM(CANAL_CEJA_DER, 0, gradosAPulsoCeja(i));
    delay(VELOCIDAD);
  }
  // Bajar (invertido)
  for (int i = CEJA_DER_MIN; i <= CEJA_DER_MAX; i++) {
    pca.setPWM(CANAL_CEJA_DER, 0, gradosAPulsoCeja(i));
    delay(VELOCIDAD);
  }
}