# Wall-E Animatrónico 🤖

Proyecto universitario de diseño mecatrónico. Animatrónico inspirado en Wall-E, controlado en tiempo real desde una app web a través de WiFi.

## Equipo

| Integrante | Área |
|---|---|
| [Nombre] | Control (app + comunicación) |
| [Nombre] | Hardware (motores, servos, estructura) |
| [Nombre] | [Área] |
| [Nombre] | [Área] |
| [Nombre] | [Área] |

## Arquitectura del sistema

```
[Celular] ←— WiFi —→ [ESP32 Access Point]
                            ↓
                     WebSocket server
                            ↓
                     Control del hardware
```

- **App**: Página web servida desde el ESP32, accesible en `192.168.4.1`
- **Protocolo**: WebSockets para comunicación en tiempo real y baja latencia
- **Microcontrolador**: ESP32 en modo Access Point
- **Red**: WiFi local sin acceso a internet

## Estructura del repositorio

```
wall-e-animatronico/
│
├── README.md
│
├── control-app/
│   ├── FASE_1/     # Hello World — WebSocket básico
│   ├── FASE_2/     # Control de un servo
│   ├── FASE_3/     # Múltiples comandos
│   ├── FASE_4/     # Control de orugas
│   └── FASE_5/     # Panel completo
│
└── hardware/       # Esquemáticos y código del hardware
```

## Plan de desarrollo

- [x] Fase 1 — Conexión WebSocket básica
- [ ] Fase 2 — Control de un servo
- [ ] Fase 3 — Múltiples comandos
- [ ] Fase 4 — Control de orugas
- [ ] Fase 5 — Panel de control completo

## Stack tecnológico

**ESP32 (PlatformIO + Arduino framework)**
- `ESPAsyncWebServer` — servidor web y WebSocket
- `AsyncTCP` — dependencia asíncrona

**App (HTML + JavaScript)**
- WebSocket API nativa del navegador
- Sin frameworks externos

## Cómo probar

1. Flashear el firmware de la fase correspondiente al ESP32
2. Conectar el celular al WiFi `WallE-Control` (contraseña: `walle1234`)
3. Abrir el navegador en `192.168.4.1`

## Hardware recomendado

- ESP32-WROOM-32U (con conector para antena externa)
- Antena omnidireccional 2.4GHz 5dBi (para uso en exteriores)
