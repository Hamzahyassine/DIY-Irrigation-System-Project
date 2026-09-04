# ESP32 Dual-Plant Irrigation System

## Why I Built This

I built this project as a hands-on way to learn embedded systems, sensors, relays, Wi-Fi, and Git. I started with an Arduino Uno design and began moving the project to an ESP32 so I could explore wireless updates and a more capable microcontroller.

## What It Does

The system monitors two plants independently. Every 60 seconds, the ESP32 reads both capacitive soil-moisture sensors. When a plant is dry, its relay activates a 5 V pump for one second.

The project is currently a work in progress. I am using the build to learn by testing, documenting mistakes, and improving the design over time.

## Current Build

- ESP32 DevKit v1
- 2 capacitive soil-moisture sensors
- 2 relay modules
- 2 x 5 V submersible pumps
- Separate power supply for the pumps
- Wi-Fi connection with ArduinoOTA support
- Serial monitoring at `9600` baud

### Pin Connections

| Function | ESP32 GPIO |
| --- | ---: |
| Sensor 1 power | 26 |
| Sensor 2 power | 27 |
| Sensor 1 analog output | 34 |
| Sensor 2 analog output | 35 |
| Pump 1 relay | 33 |
| Pump 2 relay | 32 |

GPIO 34 and GPIO 35 are input-only pins, which makes them suitable for the analog sensor outputs.

## How the Logic Works

1. The ESP32 connects to Wi-Fi during startup.
2. Each sensor is powered only while it is being read.
3. A reading above `2500` is currently treated as dry soil.
4. The matching pump runs for `1000` milliseconds.
5. The readings and watering decisions are printed to the serial monitor.

The relay modules use active-low logic: `LOW` turns a pump on and `HIGH` turns it off.

## What I Am Learning

This project has helped me understand the difference between Arduino sketches and PlatformIO projects, how GPIO pins control hardware, why ESP32 ADC pins differ from Uno analog pins, and how a Git commit records a project snapshot. My experiments and decisions are recorded in [PROGRESSION.md](PROGRESSION.md).

## Running the Project

The project uses PlatformIO with the `esp32dev` environment. The first firmware upload should be done over USB. Once Wi-Fi is configured and the ESP32 is connected, later uploads can use ArduinoOTA. The OTA address is set in `platformio.ini`.

Do not commit real Wi-Fi credentials to GitHub. Pumps should have an appropriate external power supply and must not be powered directly from an ESP32 GPIO pin.

## Future Ideas

- Calibrate each sensor separately instead of using one fixed threshold.
- Add a water-level sensor to the reservoir.
- Add a real-time clock for scheduled watering.
- Explore ESP32 deep sleep for lower power use, and exploring battery and solar powered system.
- Add maximum daily watering limits and manual pump control.
- Improve Wi-Fi credential storage.
- Create a web interface which will include soil moisture level, tank level, and manual watering.
