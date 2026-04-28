#pragma once
#include <ESPAsyncWebServer.h>
#include <Adafruit_PWMServoDriver.h>
#include "config.h"
#include "cejas.h"
#include "ojos.h"
#include "cuello.h"
#include "brazos.h"

// ─── Manejador de eventos WebSocket ──────────────────────────────────────────
inline void onWsEvent(AsyncWebSocket* server, AsyncWebSocketClient* client,
                      AwsEventType type, void* arg, uint8_t* data, size_t len,
                      Adafruit_PWMServoDriver& pca) {

  if (type == WS_EVT_CONNECT) {
    Serial.printf("Cliente conectado. ID: %u\n", client->id());

  } else if (type == WS_EVT_DISCONNECT) {
    // Detener todo movimiento al desconectarse
    ojosSubiendo    = false;
    ojosBajando     = false;
    cuelloIzq       = false;
    cuelloDer       = false;
    brazoIzqSubiendo = false;
    brazoIzqBajando  = false;
    brazoDerSubiendo = false;
    brazoDerBajando  = false;
    Serial.printf("Cliente desconectado. ID: %u\n", client->id());

  } else if (type == WS_EVT_DATA) {
    String msg = "";
    for (size_t i = 0; i < len; i++) msg += (char)data[i];
    Serial.println("Comando: " + msg);

    // ── Cejas ──────────────────────────────────────────────────────────────
    if      (msg == "CEJA_IZQ_CICLO") ciclocejaIzq(pca);
    else if (msg == "CEJA_DER_CICLO") cicloCejaDer(pca);

    // ── Ojos ───────────────────────────────────────────────────────────────
    else if (msg == "OJOS_UP_PRESS")     ojosSubiendo = true;
    else if (msg == "OJOS_UP_RELEASE")   ojosSubiendo = false;
    else if (msg == "OJOS_DOWN_PRESS")   ojosBajando  = true;
    else if (msg == "OJOS_DOWN_RELEASE") ojosBajando  = false;

    // ── Cuello ─────────────────────────────────────────────────────────────
    else if (msg == "CUELLO_IZQ_PRESS")   cuelloIzq = true;
    else if (msg == "CUELLO_IZQ_RELEASE") cuelloIzq = false;
    else if (msg == "CUELLO_DER_PRESS")   cuelloDer = true;
    else if (msg == "CUELLO_DER_RELEASE") cuelloDer = false;

    // ── Brazos ─────────────────────────────────────────────────────────────
    else if (msg == "BRAZO_IZQ_UP_PRESS")     brazoIzqSubiendo = true;
    else if (msg == "BRAZO_IZQ_UP_RELEASE")   brazoIzqSubiendo = false;
    else if (msg == "BRAZO_IZQ_DOWN_PRESS")   brazoIzqBajando  = true;
    else if (msg == "BRAZO_IZQ_DOWN_RELEASE") brazoIzqBajando  = false;
    else if (msg == "BRAZO_DER_UP_PRESS")     brazoDerSubiendo = true;
    else if (msg == "BRAZO_DER_UP_RELEASE")   brazoDerSubiendo = false;
    else if (msg == "BRAZO_DER_DOWN_PRESS")   brazoDerBajando  = true;
    else if (msg == "BRAZO_DER_DOWN_RELEASE") brazoDerBajando  = false;
  }
}