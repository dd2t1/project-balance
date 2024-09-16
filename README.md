# ESPHome HX711 Weight Sensor with ESP32-S3

This project configures an ESP32-S3 development board to use a HX711 weight sensor for real-time weight measurements. The ESP32-S3 is integrated with ESPHome, allowing communication via Wi-Fi and MQTT to a local broker. The sensor data is calibrated and optimized with filters to ensure accuracy.

## Features

- **HX711 Weight Sensor**: Measures weight using a load cell and HX711 ADC.
- **Wi-Fi Integration**: Connects to the local network for data transmission.
- **MQTT Support**: Publishes weight data to an MQTT broker.
- **OTA Updates**: Over-the-air firmware updates for easy maintenance.
- **Filters & Calibration**: Includes linear calibration and delta filtering to reduce unnecessary updates.

## Hardware

- **ESP32-S3 DevKitC-1**: Main microcontroller.
- **HX711**: Analog-to-digital converter for the load cell.
- **Load Cell**: Measures weight.
  
## Wiring

- **DOUT (HX711)** → GPIO 1 (ESP32-S3)
- **CLK (HX711)** → GPIO 2 (ESP32-S3)

## Configuration

### Wi-Fi & MQTT

Modify the Wi-Fi SSID, password, and MQTT broker address in the `esphome` YAML file.

```yaml
wifi:
  ssid: "Your-WiFi-SSID"
  password: "Your-WiFi-Password"

mqtt:
  broker: "192.168.129.188"  # Update with your broker IP address
```
Calibration
The HX711 sensor is calibrated with two reference points:

702796 corresponds to 0g.
848243 corresponds to 180g.
Adjust these values in the calibrate_linear filter to match your sensor's characteristics.

Installation
Flash the ESP32-S3 with ESPHome firmware.
Connect the ESP32-S3 to your Wi-Fi network.
Connect the MQTT broker to receive weight data.
Adjust the calibration values for accurate weight measurements.
Usage
