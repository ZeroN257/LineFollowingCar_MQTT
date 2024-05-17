Line Following Car with MQTT
Welcome to the Line Following Car project! This project utilizes MQTT to collect direction commands for a car built with NodeMCU, Arduino, a line sensor, and an L298 motor driver.

Table of Contents
Introduction
Components
Circuit Diagram
Setup
Installation
Usage
MQTT Configuration
Contributing
License
Introduction
This project aims to build a line-following car controlled via MQTT. The car follows a predefined path using a line sensor and can receive direction commands through an MQTT broker. The main components include NodeMCU for MQTT communication, Arduino for processing sensor data, a line sensor for detecting the path, and an L298 motor driver for controlling the motors.

Components
NodeMCU (ESP8266)
Arduino (e.g., Arduino Uno)
Line sensor module
L298 motor driver
DC motors
Chassis for the car
Wheels
Power supply (battery)
Connecting wires
Circuit Diagram

Setup
Connect the Components:

Connect the line sensor to the Arduino.
Connect the L298 motor driver to the motors, power supply, and Arduino.
Connect the NodeMCU to the Arduino via serial communication.
Arduino Setup:

Connect the line sensor to the Arduino analog pins.
Connect the motor driver input pins to the Arduino digital pins.
NodeMCU Setup:

Connect the NodeMCU to a Wi-Fi network.
Set up serial communication between NodeMCU and Arduino.
Installation
Clone the Repository:

bash
Copy code
git clone https://github.com/yourusername/line-following-car.git
cd line-following-car
Arduino Code:

Upload the line_following_car.ino file to your Arduino using the Arduino IDE.
NodeMCU Code:

Upload the nodemcu_mqtt.ino file to your NodeMCU using the Arduino IDE.
Libraries:

Ensure you have the required libraries installed in your Arduino IDE:
PubSubClient for MQTT
ESP8266WiFi for NodeMCU
Usage
Power the Car:

Connect the power supply to the car.
Ensure all components are powered and properly connected.
MQTT Broker:

Set up an MQTT broker (e.g., Mosquitto).
Note the broker’s IP address and port number.
Start the Car:

Place the car on the line track.
Power up the car and ensure it connects to the MQTT broker.
Send MQTT Commands:

Use an MQTT client to send direction commands to the car. Commands can include:
start to begin following the line
stop to halt the car
left to turn left
right to turn right
MQTT Configuration
Configure the MQTT settings in the nodemcu_mqtt.ino file:

cpp
Copy code
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* mqtt_server = "your_MQTT_BROKER_IP";
const int mqtt_port = your_MQTT_BROKER_PORT;
const char* mqtt_user = "your_MQTT_USERNAME";
const char* mqtt_password = "your_MQTT_PASSWORD";
Contributing
Contributions are welcome! Please fork the repository and submit a pull request with your changes. Ensure that your code adheres to the project’s coding standards and includes appropriate documentation.

License
This project is licensed under the MIT License. See the LICENSE file for details.
