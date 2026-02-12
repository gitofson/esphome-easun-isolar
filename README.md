# Still under development !!! The functionality according this readme probably won't work.
# esphome-easun-isolar
ESPHome integration for Easun iSolar SMG II inverters via RS232/Modbus RTU for Home Assistant.

# ESPHome Integration for Easun iSolar SMG II

This project provides an ESPHome configuration and custom components to integrate **Easun iSolar SMG II** inverters into **Home Assistant** using an ESP32 or ESP8266.

## Features
- Real-time data monitoring (PV Voltage, Battery Capacity, Load Wattage, etc.)
- Modbus RTU communication over RS232.
- Easy integration using ESPHome Packages.
- Support for Home Assistant Energy Dashboard.

## Hardware Requirements
- **ESP32** (recommended) or ESP8266.
- **RS232 to TTL Converter** (e.g., MAX3232) to connect the ESP to the inverter's RJ45 port.
- Appropriate cables (RJ45 to DB9/Wires).

## Wiring Diagram

> [!CAUTION]
> Never connect the inverter's RJ45 port directly to the ESP32 pins! You must use an **RS232-to-TTL converter** (e.g., MAX3232). Direct connection will destroy your ESP32.

### RJ45 to DB9 (Standard Inverter Cable)
If you are using a standard RJ45-to-DB9 cable (often supplied with the inverter) and connecting it to a MAX3232 board with a DB9 connector:

| Inverter (RJ45) | DB9 Pin | Signal | Note |
| :--- | :--- | :--- | :--- |
| **Pin 1** | **Pin 2** | RS232-TX | Connects to DB9 RX |
| **Pin 2** | **Pin 3** | RS232-RX | Connects to DB9 TX |
| **Pin 8** | **Pin 5** | GND | Common Ground |

### RS232-TTL Converter to ESP32 (C6 Example)
Wiring between the converter module and your ESP:

| MAX3232 Module | ESP32-C6 Pin | Description |
| :--- | :--- | :--- |
| **VCC** | **3.3V** | Power (check your module voltage!) |
| **GND** | **GND** | Ground |
| **TXD** | **GPIO7** (RX) | Transmit to ESP Receive |
| **RXD** | **GPIO6** (TX) | Receive from ESP Transmit |

## Quick Start


For security reasons, sensitive information like WiFi passwords and API keys are stored in a separate file named secrets.yaml. This prevents you from accidentally sharing your credentials when sharing your configuration.
Create a file named secrets.yaml in your ESPHome directory.
Copy and paste the following template:

```yaml
# secrets.yaml
wifi_ssid: "Your_WiFi_Name"
wifi_password: "Your_WiFi_Password"
# Generate a key using: esphome generate-key
api_encryption_key: "Your_Generated_API_Key"
# Password for OTA updates
ota_password: "Your_OTA_Password if any"
```
Add this to your ESPHome YAML configuration:

```yaml
esphome:
  name: isolar-bridge
  friendly_name: ISolar Bridge C6

esp32:
  board: esp32-c6-devkitc-1
  variant: esp32c6
  framework:
    type: esp-idf # C6 vyžaduje esp-idf pro plnou podporu všech funkcí

# Native API pro Home Assistant (Tohle nahrazuje MQTT)
api:
  encryption:
    key: !secret api_encryption_key

ota:
  - platform: esphome
#   password: !secret ota_password

logger:
  level: DEBUG
  baud_rate: 0 # Tohle vypne HW UART, ale nechá běžet síťový log

# Pro jistotu zapni webové rozhraní, ať se tam můžeš kouknout napřímo přes IP
#web_server:
#  port: 80

captive_portal:
# for wifi ap

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password
  ap:
    ssid: "esphome-easun-isolar Fallback Hotspot"
    password: "myfbpass"

substitutions:
  uart_tx_pin: GPIO6
  uart_rx_pin: GPIO7

packages:
  easun_logic:
    url: https://github.com/gitofson/esphome-easun-isolar
    file: easun-smg-ii.yaml
    ref: main
```
