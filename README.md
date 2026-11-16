# Displaybox

[![Build](https://github.com/mblees/Displaybox/actions/workflows/build.yml/badge.svg)](https://github.com/mblees/Displaybox/actions/workflows/build.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

A battery-powered LED light box: a 3D-printed case with a diffuser and an
exchangeable pictogram, lit from behind by WS2812 LEDs. A rotary encoder
sets the brightness and switches the colour, and an optional Wi-Fi access
point lets you pick the colour from a phone. Material cost is about **€27.50**
([pricing.md](pricing.md)).

<!-- TODO: photo of the finished box -->

## Features

- **5 modes:** orange, green, white, pink and an animated rainbow.
- **Rotary encoder (KY-040):**
  - turn → brightness (0–255 in steps of 8)
  - press → next mode
  - hold for 3 s → rainbow
- **Optional web interface:** the ESP32 opens its own Wi-Fi access point and
  serves a page with one large button per mode at `http://192.168.1.1`.
  Disabled by default, see [below](#web-interface).
- **Battery-powered:** 2 × 18650 cells on a battery shield.

## Hardware

| Part | Notes |
|---|---|
| ESP32 DevKit V1 | |
| WS2812 LEDs | count set by `MODULE_LED_AMOUNT` in [`include/main.h`](include/main.h) |
| KY-040 rotary encoder | with push button |
| 18650 Battery Shield V8 + 2 × 18650 cells | power supply |
| 3D-printed box, diffuser, pictogram | PETG |

Full parts list with prices: [pricing.md](pricing.md).

### Wiring

| Signal | ESP32 GPIO |
|---|---|
| WS2812 DIN | GPIO13 |
| KY-040 CLK | GPIO32 |
| KY-040 DT | GPIO25 |
| KY-040 SW | GPIO33 |

## Build and flash

Requires [PlatformIO](https://platformio.org/).

```bash
pio run -t upload
pio device monitor      # 9600 baud
```

## Web interface

1. Copy `include/secrets_example.h` to `include/secrets.h` and set the access
   point name and password (at least 8 characters). `secrets.h` is ignored by git.
2. Enable the web server in `platformio.ini`:

   ```ini
   build_flags = -D ENABLE_WEB_SERVER=1
   ```

3. Flash, connect to the access point and open `http://192.168.1.1`.

## How it works

- **Encoder:** decoded in an interrupt on the CLK edge; every step changes the
  brightness by 8, clamped to 0–255 ([`src/KY040.cpp`](src/KY040.cpp)). The
  push button is debounced in software and also detects a 3-second hold.
- **LEDs:** [`src/led_controller.cpp`](src/led_controller.cpp) redraws the strip
  every 10 ms with the Adafruit NeoPixel library. The rainbow spreads the colour
  wheel across all LEDs and shifts it one step per frame.
- **Web server:** [`src/web_server.cpp`](src/web_server.cpp) runs the ESP32 as
  a soft access point with a fixed IP. Each mode has its own URL (`/green`,
  `/orange`, `/white`, `/pink`, `/rainbow`).

## License

[MIT](LICENSE)
