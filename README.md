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
Add this to your ESPHome YAML configuration:

```yaml
packages:
  easun_inverter:
    url: github://gitofson/esphome-easun-isolar
    file: easun-smg-ii.yaml
    ref: v1.0.0
