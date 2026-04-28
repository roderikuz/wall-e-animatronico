#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_PWMServoDriver.h>
#include "config.h"
#include "html.h"
#include "ojos.h"
#include "cuello.h"
#include "brazos.h"
#include "websocket.h"

// ─── PCA9685 ──────────────────────────────────────────────────────────────────
Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver();

// ─── Servidor web y WebSocket ─────────────────────────────────────────────────
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// ─── Variables de estado — ojos ───────────────────────────────────────────────
bool ojosSubiendo     = false;
bool ojosBajando      = false;
int posOjoIzq         = OJO_IZQ_MIN;
int posOjoDer         = OJO_DER_MAX;
unsigned long ultimoMovOjos = 0;

// ─── Variables de estado — cuello ────────────────────────────────────────────
bool cuelloIzq        = false;
bool cuelloDer        = false;
int posCuello         = CUELLO_CENTRO;
unsigned long ultimoMovCuello = 0;

// ─── Variables de estado — brazos ────────────────────────────────────────────
bool brazoIzqSubiendo = false;
bool brazoIzqBajando  = false;
bool brazoDerSubiendo = false;
bool brazoDerBajando  = false;
int posBrazoIzq       = BRAZO_IZQ_MAX;
int posBrazoDer       = BRAZO_DER_MIN;
unsigned long ultimoMovBrazos = 0;

// ─── Callback WebSocket ───────────────────────────────────────────────────────
void wsCallback(AsyncWebSocket* server, AsyncWebSocketClient* client,
                AwsEventType type, void* arg, uint8_t* data, size_t len) {
  onWsEvent(server, client, type, arg, data, len, pca);
}

// ─── Configuración inicial ────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);

  // Inicializa I2C y PCA9685
  Wire.begin();
  pca.begin();
  pca.setPWMFreq(PWM_FREQ);
  Serial.println("PCA9685 inicializado");

  // Posiciones iniciales
  pca.setPWM(CANAL_OJO_IZQ,  0, map(OJO_IZQ_MIN,    0, 180, SERVOMIN, SERVOMAX));
  pca.setPWM(CANAL_OJO_DER,  0, map(OJO_DER_MAX,    0, 180, SERVOMIN, SERVOMAX));
  pca.setPWM(CANAL_CUELLO,   0, map(CUELLO_CENTRO,   0, 180, SERVOMIN, SERVOMAX));
  pca.setPWM(CANAL_CEJA_IZQ, 0, map(CEJA_IZQ_MIN,   0, 180, SERVOMIN, SERVOMAX));
  pca.setPWM(CANAL_CEJA_DER, 0, map(CEJA_DER_MAX,   0, 180, SERVOMIN, SERVOMAX));
  pca.setPWM(CANAL_BRAZO_IZQ,0, map(BRAZO_IZQ_MAX,  0, 180, SERVOMIN, SERVOMAX));
  pca.setPWM(CANAL_BRAZO_DER,0, map(BRAZO_DER_MIN,  0, 180, SERVOMIN, SERVOMAX));
  Serial.println("Servos en posicion inicial");

  // Crea la red WiFi
  WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());

  // Registra WebSocket y servidor
  ws.onEvent(wsCallback);
  server.addHandler(&ws);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/html", index_html);
  });

  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

// ─── Bucle principal ──────────────────────────────────────────────────────────
void loop() {
  ws.cleanupClients();
  actualizarOjos(pca);
  actualizarCuello(pca);
  actualizarBrazos(pca);
}