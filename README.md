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
- WiFi Hotspot: NodeMCU creates a WiFi hotspot.
- Web Server: NodeMCU hosts a web server to receive HTTP requests.
- Serial Communication: NodeMCU sends commands to the Arduino via serial communication.
- Motor Control: Arduino controls the motors based on the commands received.

## Setup

### Hardware Connections:
- Stack the Motor Driver Shield L293D on the Arduino.
- Connect the motors to the motor driver shield.
- Connect the TX pin of NodeMCU to the RX pin of Arduino.
- Connect the RX pin of NodeMCU to the TX pin of Arduino.
- Connect the GND of NodeMCU to the GND of Arduino.

