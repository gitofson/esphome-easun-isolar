# Still under development !!! The functionality according this readme probably won't work.
# esphome-easun-isolar
ESPHome integration for Easun iSolar SMG II inverters via RS232/Modbus RTU for Home Assistant.

# ESPHome Integration for Easun iSolar SMG II

This project provides an ESPHome configuration and custom components to integrate **Easun iSolar SMG II** inverters into **Home Assistant** using an ESP32 or ESP8266.

## Features
- Real-time data monitoring (PV Voltage, Battery Capacity, Load Wattage, etc.)
- Modbus RTU communication over RS232.
- Easy integration as an `external_component`.
- Support for Home Assistant Energy Dashboard.

## Hardware Requirements
- **ESP32** (recommended) or ESP8266.
- **RS232 to TTL Converter** (e.g., MAX3232) to connect the ESP to the inverter's RJ45 port.
- Appropriate cables (RJ45 to DB9/Wires).

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
