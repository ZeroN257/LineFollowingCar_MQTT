#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>

const char* ssid = "Ngu";
const char* password = "123123123";
const char* mqtt_server = "192.168.83.246";
const char* mqtt_topic = "exe/direction";

WiFiClient espClient;
PubSubClient client(espClient);
SoftwareSerial mySerial(D7, D8); // RX, TX

// Define the mapping for directions
const char* directions[] = {"forward", "left", "right"};

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600); // SoftwareSerial initialization

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Connect to MQTT broker
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  reconnect();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect("NodeMCU_Client")) {
      Serial.println("Connected to MQTT broker");
      // Subscribe to the desired topic
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Received message on topic: ");
  Serial.println(topic);

  Serial.print("Message: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Process the received message
  processCommands((char*)payload, length);
}

void processCommands(char* message, unsigned int length) {
  // Convert the received message to a String
  String commandsString = String(message);

  // Split the string into commands using ","
  String commandsArray[50]; // Adjust the array size based on your maximum expected commands
  int commandsCount = splitString(commandsString, ',', commandsArray);

  // Map string commands to numeric values and send to Arduino Uno via SoftwareSerial
  for (int i = 0; i < commandsCount; i++) {
    String command = commandsArray[i];

    // Check if the command is "forward", "left", or "right" and map to numeric values
    if (command.equalsIgnoreCase("forward")) {
      mySerial.print("0,");
    } else if (command.equalsIgnoreCase("left")) {
      mySerial.print("1,");
    } else if (command.equalsIgnoreCase("right")) {
      mySerial.print("2,");
    }
  }
  mySerial.println(); // Send a newline character to indicate the end of the message
}


int splitString(String inputString, char separator, String outputArray[]) {
  int arrayIndex = 0;
  int separatorIndex = inputString.indexOf(separator);
  while (separatorIndex != -1) {
    outputArray[arrayIndex++] = inputString.substring(0, separatorIndex);
    inputString = inputString.substring(separatorIndex + 1);
    separatorIndex = inputString.indexOf(separator);
  }
  // Add the last part of the string
  outputArray[arrayIndex++] = inputString;
  return arrayIndex;
}
