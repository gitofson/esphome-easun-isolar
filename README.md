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

### Inverter RJ45 Pinouts Comparison
Depending on your inverter model, the RJ45 port layout differs. Please wire your cable accordingly:

| Pin | SMG-II (`easun-smg-ii.yaml`) | Axpert V3 (`axpert-v3-power.yaml`) | **iSolar SMT 12KP** (`easun-smt-12kp.yaml`) |
| :---: | :--- | :--- | :--- |
| **Pin 1** | **RS232-TX** (Data from Inverter) | **RS232-TX** (Data from Inverter) | NC (Not Connected) |
| **Pin 2** | **RS232-RX** (Data to Inverter) | **RS232-RX** (Data to Inverter) | **+12V DC** (Power output) |
| **Pin 3** | **GND** (Common Ground) | **GND** (Common Ground) | **RS232-TX** (Data from Inverter) |
| **Pin 4** | NC | NC | NC |
| **Pin 5** | +14V DC (Power output) | +14V DC (Power output) | **GND** (Common Ground) |
| **Pin 6** | NC | NC | **RS232-RX** (Data to Inverter) |
| **Pin 7** | NC | NC | NC |
| **Pin 8** | NC | NC | NC |

---

### RJ45 to DB9 (Standard Inverter Cable)
Wiring schematic when adapting the RJ45 port to a standard DB9 female connector on a MAX3232 board:

#### For SMG-II & Axpert V3:

| Inverter (RJ45) | DB9 Pin | Signal | Note |
| :--- | :--- | :--- | :--- |
| **Pin 1** | **Pin 2** | RS232-TX | Connects to DB9 RX |
| **Pin 2** | **Pin 3** | RS232-RX | Connects to DB9 TX |
| **Pin 3** | **Pin 5** | GND | Common Ground |

#### For iSolar SMT 12KP:

| Inverter (RJ45) | DB9 Pin | Signal | Note |
| :--- | :--- | :--- | :--- |
| **Pin 3** | **Pin 2** | RS232-TX | Connects to DB9 RX (Data from Inverter) |
| **Pin 6** | **Pin 3** | RS232-RX | Connects to DB9 TX (Data to Inverter) |
| **Pin 5** | **Pin 5** | GND | Common Ground |


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
    type: esp-idf # for C6 

# Native API pro Home Assistant (Tohle nahrazuje MQTT)
api:
  encryption:
    key: !secret api_encryption_key

ota:
  - platform: esphome
#   password: !secret ota_password

logger:
  level: DEBUG
  baud_rate: 0 # Turn off HW UART and net log running

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
#    file: easun-smg-ii.yaml #rj45 pinout (inverter side): Tx, Rx, GND, NC, +14V
#    file: axpert-v3-power.yaml #rj45 pinout (inverter side): Tx, Rx, GND, NC, +14V
#    file: easun-smg-12kp.yaml #rj45 pinout (inverter side): NC, +12V, Tx, NC, GND, Rx 
packages:
  easun_logic:
    url: https://github.com/gitofson/esphome-easun-isolar
    file: easun-smg-ii.yaml
    ref: main
    refresh: 0s
```
