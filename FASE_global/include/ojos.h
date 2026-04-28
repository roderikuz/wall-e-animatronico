#pragma once
#include <Adafruit_PWMServoDriver.h>
#include "config.h"

// ─── Estado de movimiento de ojos ────────────────────────────────────────────
extern bool ojosSubiendo;
extern bool ojosBajando;
extern int posOjoIzq;
extern int posOjoDer;
extern unsigned long ultimoMovOjos;

// ─── Convierte grados a pulso ─────────────────────────────────────────────────
inline int gradosAPulsoOjo(int grados) {
  return map(grados, 0, 180, SERVOMIN, SERVOMAX);
}

// ─── Actualiza posición de ojos en el loop ───────────────────────────────────
inline void actualizarOjos(Adafruit_PWMServoDriver& pca) {
  unsigned long ahora = millis();
  if (ahora - ultimoMovOjos < VELOCIDAD) return;
  ultimoMovOjos = ahora;

  if (ojosSubiendo) {
    // Ojo izquierdo sube
    if (posOjoIzq < OJO_IZQ_MAX) {
      posOjoIzq++;
      pca.setPWM(CANAL_OJO_IZQ, 0, gradosAPulsoOjo(posOjoIzq));
    }
    // Ojo derecho sube (invertido)
    if (posOjoDer > OJO_DER_MIN) {
      posOjoDer--;
      pca.setPWM(CANAL_OJO_DER, 0, gradosAPulsoOjo(posOjoDer));
    }

  } else if (ojosBajando) {
    // Ojo izquierdo baja
    if (posOjoIzq > OJO_IZQ_MIN) {
      posOjoIzq--;
      pca.setPWM(CANAL_OJO_IZQ, 0, gradosAPulsoOjo(posOjoIzq));
    }
    // Ojo derecho baja (invertido)
    if (posOjoDer < OJO_DER_MAX) {
      posOjoDer++;
      pca.setPWM(CANAL_OJO_DER, 0, gradosAPulsoOjo(posOjoDer));
    }
  }
}