#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Credenciales de tu Access Point
const char* ssid     = "WallE-Control";
const char* password = "walle1234";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Página HTML embebida en el firmware
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
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
    }
  </style>
</head>
<body>
  <button ontouchstart="enviar('PING')" onmousedown="enviar('PING')">
    ¡Presionar!
  </button>

  <script>
    var ws = new WebSocket('ws://' + location.hostname + '/ws');

    ws.onopen    = function() { console.log('WebSocket conectado'); };
    ws.onclose   = function() { console.log('WebSocket desconectado'); };
    ws.onerror   = function(e) { console.log('Error: ', e); };

    function enviar(cmd) {
      if (ws.readyState === WebSocket.OPEN) {
        ws.send(cmd);
      }
    }
  </script>
</body>
</html>
)rawliteral";

// Manejador de eventos WebSocket
void onWsEvent(AsyncWebSocket* server, AsyncWebSocketClient* client,
               AwsEventType type, void* arg, uint8_t* data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    Serial.printf("Cliente conectado. ID: %u\n", client->id());

  } else if (type == WS_EVT_DISCONNECT) {
    Serial.printf("Cliente desconectado. ID: %u\n", client->id());

  } else if (type == WS_EVT_DATA) {
    // Reconstruir el mensaje recibido
    String msg = "";
    for (size_t i = 0; i < len; i++) msg += (char)data[i];
    Serial.println("Comando recibido: " + msg);
  }
}

void setup() {
  Serial.begin(115200);

  // Crear Access Point
  WiFi.softAP(ssid, password);
  Serial.println("\nAccess Point iniciado");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("IP:   ");
  Serial.println(WiFi.softAPIP()); // Normalmente 192.168.4.1

  // Registrar WebSocket en el servidor
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  // Ruta principal — sirve la página HTML
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/html", index_html);
  });

  server.begin();
  Serial.println("Servidor HTTP iniciado\n");
}

void loop() {
  ws.cleanupClients(); // Limpia conexiones inactivas
}

//Esto es una prueba 