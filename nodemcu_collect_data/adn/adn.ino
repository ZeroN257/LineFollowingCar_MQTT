#include <SoftwareSerial.h>

SoftwareSerial mySerial(0, 1); // RX, TX

void setup() {
  Serial.begin(9600); // Serial Monitor
  mySerial.begin(9600); // SoftwareSerial initialization
}

void loop() {
  if (mySerial.available() > 0) {
    char receivedChar = mySerial.read();
    Serial.print(receivedChar);

    // Print a newline if the received character is ']'
    if (receivedChar == ']') {
      Serial.println();
    }
  }
}
