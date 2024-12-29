# Gauhartas8266 ESPHome Project

This project is designed to control and monitor home automation devices using an ESP8266-based microcontroller. It integrates with Home Assistant and communicates with UART-enabled devices to manage lights, sensors, and valves.

## Features

- **Home Assistant Integration**: Control and monitor devices through Home Assistant API.
- **UART Communication**: Send and receive commands via UART to control connected devices.
- **Web Interface**: Includes a simple web server for basic interaction.
- **OTA Updates**: Easily update the firmware wirelessly.
- **Custom UART Line Sensor**: Reads and parses UART messages to update the device state in real-time.
- **Fallback Hotspot**: Automatically creates an access point if the Wi-Fi connection fails.

## System Overview

The system works as follows:
1. The ESP8266 device communicates with peripherals via UART using defined commands.
2. Incoming UART messages are parsed by the custom `UartReadLineSensor` class.
3. Device states are updated in Home Assistant based on parsed data.
4. Commands can be sent from Home Assistant or the web interface to control devices.

### Diagram

```plaintext
[Home Assistant] <--API--> [ESP8266 (Gauhartas8266)] <--UART--> [Devices]
