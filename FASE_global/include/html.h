#pragma once

const char index_html[] = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Wall-E Control</title>
  <style>
    * { box-sizing: border-box; margin: 0; padding: 0; }

    body {
      background: #111;
      color: #fff;
      font-family: sans-serif;
      padding: 20px;
    }

    h2 {
      text-align: center;
      color: #f0a500;
      margin-bottom: 20px;
      font-size: 24px;
    }

    .seccion {
      margin-bottom: 24px;
    }

    .seccion h3 {
      font-size: 14px;
      color: #aaa;
      text-transform: uppercase;
      letter-spacing: 1px;
      margin-bottom: 10px;
      border-bottom: 1px solid #333;
      padding-bottom: 6px;
    }

    .fila {
      display: flex;
      gap: 12px;
      flex-wrap: wrap;
    }

    button {
      flex: 1;
      min-width: 120px;
      padding: 18px 10px;
      font-size: 16px;
      font-weight: bold;
      border: none;
      border-radius: 12px;
      cursor: pointer;
      user-select: none;
      color: #111;
      background: #f0a500;
    }

    button.azul {
      background: #4a90d9;
      color: #fff;
    }
  </style>
</head>
<body>

  <h2>Wall-E Control</h2>

  <!-- CEJAS -->
  <div class="seccion">
    <h3>Cejas</h3>
    <div class="fila">
      <button onclick="enviar('CEJA_IZQ_CICLO')">
        Ceja Izquierda
      </button>
      <button onclick="enviar('CEJA_DER_CICLO')">
        Ceja Derecha
      </button>
    </div>
  </div>

  <!-- OJOS -->
  <div class="seccion">
    <h3>Ojos</h3>
    <div class="fila">
      <button
        onmousedown="enviar('OJOS_UP_PRESS')"     ontouchstart="enviar('OJOS_UP_PRESS')"
        onmouseup="enviar('OJOS_UP_RELEASE')"     ontouchend="enviar('OJOS_UP_RELEASE')">
        ▲ Subir
      </button>
      <button class="azul"
        onmousedown="enviar('OJOS_DOWN_PRESS')"   ontouchstart="enviar('OJOS_DOWN_PRESS')"
        onmouseup="enviar('OJOS_DOWN_RELEASE')"   ontouchend="enviar('OJOS_DOWN_RELEASE')">
        ▼ Bajar
      </button>
    </div>
  </div>

  <!-- CUELLO -->
  <div class="seccion">
    <h3>Cuello</h3>
    <div class="fila">
      <button
        onmousedown="enviar('CUELLO_IZQ_PRESS')"   ontouchstart="enviar('CUELLO_IZQ_PRESS')"
        onmouseup="enviar('CUELLO_IZQ_RELEASE')"   ontouchend="enviar('CUELLO_IZQ_RELEASE')">
        ◀ Izquierda
      </button>
      <button class="azul"
        onmousedown="enviar('CUELLO_DER_PRESS')"   ontouchstart="enviar('CUELLO_DER_PRESS')"
        onmouseup="enviar('CUELLO_DER_RELEASE')"   ontouchend="enviar('CUELLO_DER_RELEASE')">
        Derecha ▶
      </button>
    </div>
  </div>

  <!-- BRAZOS -->
  <div class="seccion">
    <h3>Brazo Izquierdo</h3>
    <div class="fila">
      <button
        onmousedown="enviar('BRAZO_IZQ_UP_PRESS')"     ontouchstart="enviar('BRAZO_IZQ_UP_PRESS')"
        onmouseup="enviar('BRAZO_IZQ_UP_RELEASE')"     ontouchend="enviar('BRAZO_IZQ_UP_RELEASE')">
        ▲ Subir
      </button>
      <button class="azul"
        onmousedown="enviar('BRAZO_IZQ_DOWN_PRESS')"   ontouchstart="enviar('BRAZO_IZQ_DOWN_PRESS')"
        onmouseup="enviar('BRAZO_IZQ_DOWN_RELEASE')"   ontouchend="enviar('BRAZO_IZQ_DOWN_RELEASE')">
        ▼ Bajar
      </button>
    </div>
  </div>

  <div class="seccion">
    <h3>Brazo Derecho</h3>
    <div class="fila">
      <button
        onmousedown="enviar('BRAZO_DER_UP_PRESS')"     ontouchstart="enviar('BRAZO_DER_UP_PRESS')"
        onmouseup="enviar('BRAZO_DER_UP_RELEASE')"     ontouchend="enviar('BRAZO_DER_UP_RELEASE')">
        ▲ Subir
      </button>
      <button class="azul"
        onmousedown="enviar('BRAZO_DER_DOWN_PRESS')"   ontouchstart="enviar('BRAZO_DER_DOWN_PRESS')"
        onmouseup="enviar('BRAZO_DER_DOWN_RELEASE')"   ontouchend="enviar('BRAZO_DER_DOWN_RELEASE')">
        ▼ Bajar
      </button>
    </div>
  </div>

  <script>
    var ws = new WebSocket('ws://' + location.hostname + '/ws');

    ws.onopen  = function() { console.log('WebSocket conectado'); };
    ws.onclose = function() { console.log('WebSocket desconectado'); };
    ws.onerror = function(e) { console.log('Error: ', e); };

    function enviar(cmd) {
      if (ws.readyState === WebSocket.OPEN) {
        ws.send(cmd);
      }
    }
  </script>

</body>
</html>
)rawliteral";