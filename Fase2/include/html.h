#pragma once

const char index_html[] = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Wall-E Control</title>
  <style>
    body {
      display: flex;
      flex-direction: column;
      justify-content: center;
      align-items: center;
      height: 100vh;
      background: #111;
      margin: 0;
      gap: 24px;
    }
    button {
      padding: 40px 80px;
      font-size: 28px;
      border: none;
      border-radius: 16px;
      color: #111;
      cursor: pointer;
      font-weight: bold;
      user-select: none;
    }
    #btn-up   { background: #f0a500; }
    #btn-down { background: #4a90d9; }
    #estado {
      color: #fff;
      font-size: 22px;
      font-family: sans-serif;
    }
  </style>
</head>
<body>
  <p id="estado">Posición: 15°</p>
  <button id="btn-up"
    ontouchstart="enviar('UP_PRESS')"   onmousedown="enviar('UP_PRESS')"
    ontouchend="enviar('UP_RELEASE')"   onmouseup="enviar('UP_RELEASE')">
    ▲ Avanzar
  </button>
  <button id="btn-down"
    ontouchstart="enviar('DOWN_PRESS')"   onmousedown="enviar('DOWN_PRESS')"
    ontouchend="enviar('DOWN_RELEASE')"   onmouseup="enviar('DOWN_RELEASE')">
    ▼ Retroceder
  </button>

  <script>
    var ws = new WebSocket('ws://' + location.hostname + '/ws');

    ws.onopen  = function() { console.log('WebSocket conectado'); };
    ws.onclose = function() { console.log('WebSocket desconectado'); };
    ws.onerror = function(e) { console.log('Error: ', e); };

    ws.onmessage = function(event) {
      document.getElementById('estado').innerText = 'Posición: ' + event.data + '°';
    };

    function enviar(cmd) {
      if (ws.readyState === WebSocket.OPEN) {
        ws.send(cmd);
      }
    }
  </script>
</body>
</html>
)rawliteral";