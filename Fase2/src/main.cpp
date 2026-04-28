#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "config.h"
#include "html.h"

// ─── Servidor web y WebSocket ─────────────────────────────────────────────────
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// ─── PCA9685 ──────────────────────────────────────────────────────────────────
Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver();

// ─── Estado del servo ─────────────────────────────────────────────────────────
int posActual                  = POS_MIN;
bool moviendoUp                = false;
bool moviendoDown              = false;
unsigned long ultimoMovimiento = 0;

// ─── Convierte grados a valor de pulso para el PCA9685 ───────────────────────
int gradosAPulso(int grados) {
  return map(grados, 0, 180, PULSO_MIN, PULSO_MAX);
}

// ─── Manejador de eventos WebSocket ──────────────────────────────────────────
void onWsEvent(AsyncWebSocket* server, AsyncWebSocketClient* client,
               AwsEventType type, void* arg, uint8_t* data, size_t len) {

  if (type == WS_EVT_CONNECT) {
    Serial.printf("Cliente conectado. ID: %u\n", client->id());
    client->text(String(posActual));

  } else if (type == WS_EVT_DISCONNECT) {
    moviendoUp   = false;
    moviendoDown = false;
    Serial.printf("Cliente desconectado. ID: %u\n", client->id());

  } else if (type == WS_EVT_DATA) {
    String msg = "";
    for (size_t i = 0; i < len; i++) msg += (char)data[i];

    if      (msg == "UP_PRESS")     moviendoUp   = true;
    else if (msg == "UP_RELEASE")   moviendoUp   = false;
    else if (msg == "DOWN_PRESS")   moviendoDown = true;
    else if (msg == "DOWN_RELEASE") moviendoDown = false;

    Serial.println("Comando recibido: " + msg);
  }
}

// ─── Configuración inicial ────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);

  // Inicializa I2C con los pines definidos
  Wire.begin(I2C_SDA, I2C_SCL);

  // Inicializa el PCA9685 y lo coloca en posición mínima
  pca.begin();
  pca.setPWMFreq(PWM_FREQ);
  pca.setPWM(SERVO_CANAL, 0, gradosAPulso(POS_MIN));
  Serial.println("PCA9685 inicializado");

  // Crea la red WiFi (Access Point)
  WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("\nAccess Point iniciado");
  Serial.print("SSID: ");
  Serial.println(WIFI_SSID);
  Serial.print("IP:   ");
  Serial.println(WiFi.softAPIP());

  // Registra el WebSocket en el servidor
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  // Ruta principal: sirve el HTML embebido
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/html", index_html);
  });

  server.begin();
  Serial.println("Servidor HTTP iniciado\n");
}

// ─── Bucle principal ──────────────────────────────────────────────────────────
void loop() {
  ws.cleanupClients();

  // Mueve el servo gradualmente según las banderas activas
  unsigned long ahora = millis();
  if (ahora - ultimoMovimiento >= INTERVALO) {
    ultimoMovimiento = ahora;

    if (moviendoUp && posActual < POS_MAX) {
      posActual += VELOCIDAD;
      if (posActual > POS_MAX) posActual = POS_MAX;
      pca.setPWM(SERVO_CANAL, 0, gradosAPulso(posActual));
      ws.textAll(String(posActual));
      Serial.printf("Servo -> %d°\n", posActual);

    } else if (moviendoDown && posActual > POS_MIN) {
      posActual -= VELOCIDAD;
      if (posActual < POS_MIN) posActual = POS_MIN;
      pca.setPWM(SERVO_CANAL, 0, gradosAPulso(posActual));
      ws.textAll(String(posActual));
      Serial.printf("Servo -> %d°\n", posActual);
    }
  }
}