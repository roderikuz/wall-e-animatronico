#pragma once
#include <Adafruit_PWMServoDriver.h>
#include "config.h"

// ─── Estado de movimiento de brazos ──────────────────────────────────────────
extern bool brazoIzqSubiendo;
extern bool brazoIzqBajando;
extern bool brazoDerSubiendo;
extern bool brazoDerBajando;
extern int posBrazoIzq;
extern int posBrazoDer;
extern unsigned long ultimoMovBrazos;

// ─── Convierte grados a pulso ─────────────────────────────────────────────────
inline int gradosAPulsoBrazo(int grados) {
  return map(grados, 0, 180, SERVOMIN, SERVOMAX);
}

// ─── Actualiza posición de brazos en el loop ─────────────────────────────────
inline void actualizarBrazos(Adafruit_PWMServoDriver& pca) {
  unsigned long ahora = millis();
  if (ahora - ultimoMovBrazos < VELOCIDAD) return;
  ultimoMovBrazos = ahora;

  // Brazo izquierdo (reposo en MAX, sube bajando grados)
  if (brazoIzqSubiendo && posBrazoIzq > BRAZO_IZQ_MIN) {
    posBrazoIzq--;
    pca.setPWM(CANAL_BRAZO_IZQ, 0, gradosAPulsoBrazo(posBrazoIzq));
  } else if (brazoIzqBajando && posBrazoIzq < BRAZO_IZQ_MAX) {
    posBrazoIzq++;
    pca.setPWM(CANAL_BRAZO_IZQ, 0, gradosAPulsoBrazo(posBrazoIzq));
  }

  // Brazo derecho (reposo en MIN, sube subiendo grados)
  if (brazoDerSubiendo && posBrazoDer < BRAZO_DER_MAX) {
    posBrazoDer++;
    pca.setPWM(CANAL_BRAZO_DER, 0, gradosAPulsoBrazo(posBrazoDer));
  } else if (brazoDerBajando && posBrazoDer > BRAZO_DER_MIN) {
    posBrazoDer--;
    pca.setPWM(CANAL_BRAZO_DER, 0, gradosAPulsoBrazo(posBrazoDer));
  }
}