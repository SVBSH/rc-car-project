# WiFi Controlled Motor Driver with NodeMCU and Arduino

## Description

This project demonstrates how to control motors connected to an Arduino using a NodeMCU (ESP8266) module and a Motor Driver Shield L293D. The NodeMCU creates a WiFi hotspot and hosts a simple web server. When you send HTTP requests to the server, the NodeMCU sends corresponding commands to the Arduino via serial communication to control the motors.

## Components

- NodeMCU (ESP8266)
- Arduino (any model with serial communication support)
- Motor Driver Shield L293D
- Motors
- Jumper wires

## Features

- **WiFi Hotspot**: NodeMCU creates a WiFi hotspot.
- **Web Server**: NodeMCU hosts a web server to receive HTTP requests.
- **Serial Communication**: NodeMCU sends commands to the Arduino via serial communication.
- **Motor Control**: Arduino controls the motors based on the commands received.

## Setup

### Hardware Connections:

1. Stack the Motor Driver Shield L293D on the Arduino.
2. Connect the motors to the motor driver shield.
3. Connect the TX pin of NodeMCU to the RX pin of Arduino.
4. Connect the RX pin of NodeMCU to the TX pin of Arduino.
5. Connect the GND of NodeMCU to the GND of Arduino.

### Software Setup

1. Clone the repository.
2. Open the `arduino_wifi_controller` folder in PlatformIO.
3. Install the required libraries specified in `platformio.ini`.
4. Upload the code to the NodeMCU and Arduino.

## Usage

1. Connect to the WiFi hotspot created by the NodeMCU.
2. Open a web browser and navigate to the NodeMCU's IP address (default: `192.168.4.22`).
3. Use the web interface to control the motors or use the arrow keys on your keyboard.

## Related Documentation Links

- [ESP8266 - Soft Access Point](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-examples.html)
- [ESP8266 - GitHub](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi)

## License

This project is licensed under the MIT License.
