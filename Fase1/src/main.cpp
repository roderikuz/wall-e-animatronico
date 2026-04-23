#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// ─── Credenciales del Access Point ───────────────────────────────────────────
const char* ssid     = "WallE-Control";
const char* password = "walle1234";

// ─── Servidor web y WebSocket ─────────────────────────────────────────────────
AsyncWebServer server(80);  // Puerto 80 (HTTP estándar)
AsyncWebSocket ws("/ws");   // Endpoint del WebSocket

// ─── Página HTML embebida en el firmware ─────────────────────────────────────
// Se sirve directamente desde el ESP32 al navegador del celular
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Wall-E Control</title>
  <style>
    body {
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100vh;
      background: #111;
      margin: 0;
    }
    button {
      padding: 40px 80px;
      font-size: 28px;
      background: #f0a500;
      border: none;
      border-radius: 16px;
      color: #111;
      cursor: pointer;
      font-weight: bold;
      user-select: none;
    }
  </style>
</head>
<body>
  <button
    ontouchstart="enviar('PRESS')"   onmousedown="enviar('PRESS')"
    ontouchend="enviar('RELEASE')"   onmouseup="enviar('RELEASE')">
    ¡Presionar!
  </button>

  <script>
    // Conexión WebSocket apuntando al ESP32 (misma IP que sirvió la página)
    var ws = new WebSocket('ws://' + location.hostname + '/ws');

    ws.onopen    = function() { console.log('WebSocket conectado'); };
    ws.onclose   = function() { console.log('WebSocket desconectado'); };
    ws.onerror   = function(e) { console.log('Error: ', e); };

    // Envía un comando al ESP32 si la conexión está abierta
    function enviar(cmd) {
      if (ws.readyState === WebSocket.OPEN) {
        ws.send(cmd);
      }
    }
  </script>
</body>
</html>
)rawliteral";

// ─── Manejador de eventos WebSocket ──────────────────────────────────────────
// Se ejecuta cada vez que un cliente se conecta, desconecta o envía un mensaje
void onWsEvent(AsyncWebSocket* server, AsyncWebSocketClient* client,
               AwsEventType type, void* arg, uint8_t* data, size_t len) {

  if (type == WS_EVT_CONNECT) {
    Serial.printf("Cliente conectado. ID: %u\n", client->id());

  } else if (type == WS_EVT_DISCONNECT) {
    Serial.printf("Cliente desconectado. ID: %u\n", client->id());

  } else if (type == WS_EVT_DATA) {
    // Reconstruye el mensaje recibido byte a byte
    String msg = "";
    for (size_t i = 0; i < len; i++) msg += (char)data[i];

    // Muestra en consola el estado del botón
    if (msg == "PRESS") {
      Serial.println("Botón presionado");
    } else if (msg == "RELEASE") {
      Serial.println("Botón soltado");
    }
  }
}

// ─── Configuración inicial ────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);

  // Crea la red WiFi (Access Point) con las credenciales definidas arriba
  WiFi.softAP(ssid, password);
  Serial.println("\nAccess Point iniciado");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("IP:   ");
  Serial.println(WiFi.softAPIP()); // Normalmente 192.168.4.1

  // Registra el manejador de eventos y agrega el WebSocket al servidor
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  // Ruta principal: sirve la página HTML cuando el celular entra a 192.168.4.1
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/html", index_html);
  });

  server.begin();
  Serial.println("Servidor HTTP iniciado\n");
}

// ─── Bucle principal ──────────────────────────────────────────────────────────
void loop() {
  ws.cleanupClients(); // Libera memoria de conexiones WebSocket inactivas
}