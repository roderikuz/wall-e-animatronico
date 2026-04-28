#pragma once
#include <Adafruit_PWMServoDriver.h>
#include "config.h"

// ─── Estado de movimiento del cuello ─────────────────────────────────────────
extern bool cuelloIzq;
extern bool cuelloDer;
extern int posCuello;
extern unsigned long ultimoMovCuello;

// ─── Convierte grados a pulso ─────────────────────────────────────────────────
inline int gradosAPulsoCuello(int grados) {
  return map(grados, 0, 180, SERVOMIN, SERVOMAX);
}

// ─── Actualiza posición del cuello en el loop ────────────────────────────────
inline void actualizarCuello(Adafruit_PWMServoDriver& pca) {
  unsigned long ahora = millis();
  if (ahora - ultimoMovCuello < VELOCIDAD_CUELLO) return;
  ultimoMovCuello = ahora;

  if (cuelloIzq && posCuello > CUELLO_MIN) {
    posCuello--;
    pca.setPWM(CANAL_CUELLO, 0, gradosAPulsoCuello(posCuello));

  } else if (cuelloDer && posCuello < CUELLO_MAX) {
    posCuello++;
    pca.setPWM(CANAL_CUELLO, 0, gradosAPulsoCuello(posCuello));
  }
}