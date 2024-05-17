#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1 ); // RX, TX
const int ENA = 10;
const int IN1 = 8;
const int IN2 = 9;

const int ENB = 11;
const int IN3 = 12;
const int IN4 = 13;

const int EN = 100;
const int EN_TURN = 80;
const int EN_Exe = 120;   // Speed for turning

const int Sensor1 = 2;
const int Sensor2 = 3;
const int Sensor3 = 4;
const int Sensor4 = 5;
const int Sensor5 = 6;

int carMode = 0;

// Array to store the sequence of commands (0: Forward, 1: Left, 2: Right)
int commandSequence[50];
int currentCommandIndex = 0;
int commandExecutedCount = 0;
bool commandExecuted = false;

 
  void setup() {
    Serial.begin(9600);
    mySerial.begin(9600); // SoftwareSerial initialization
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    pinMode(Sensor1, INPUT);
    pinMode(Sensor2, INPUT);
    pinMode(Sensor3, INPUT);
    pinMode(Sensor4, INPUT);
    pinMode(Sensor5, INPUT);

    delay(1000);

}

void loop() {
    

    if (mySerial.available() > 0) {
        String receivedString = "";
        char receivedChar = mySerial.read();

        // Read characters until the delimiter ']'
        while (receivedChar != ']' && mySerial.available() > 0) {
            receivedString += receivedChar;
            receivedChar = mySerial.read();
        }

        // Process the received string
        if (receivedString.length() > 0) {
            Serial.println(receivedString);

            // Update the commandSequence array
            updateCommandSequence(receivedString);
        
        }
    }


   
switch (carMode) {
    case 0:
        if (commandSequenceIsEmpty()) {
            car_stop();
            delay(5000); // Stop the car when commandSequence is empty
        } else {
            straightStick();
            if (digitalRead(Sensor1) == 0 && digitalRead(Sensor2) == 0 && digitalRead(Sensor3) == 0 &&
                digitalRead(Sensor4) == 0 && digitalRead(Sensor5) == 0) {
                if (!commandExecuted) {
                    executeCommandSequence();
                    commandExecuted = true;
                }
            } else {
                commandExecuted = false; // Reset the command execution state when sensors are not all at 0
            }
        }
        break;
}
}
bool commandSequenceIsEmpty() {
    for (int i = 0; i < 50; ++i) {
        if (commandSequence[i] != 0) {
            return false; // The array is not empty
        }
    }
    return true; // The array is empty
}

void updateCommandSequence(String receivedString) {
    int index = 0;
    //Reset execute command
    currentCommandIndex = 0;
    
    for (int i = 0; i < receivedString.length() && index < sizeof(commandSequence) / sizeof(commandSequence[0]); i++) {
        char receivedChar = receivedString.charAt(i);
        if (receivedChar >= '0' && receivedChar <= '9') {
            // Convert char to int and update the array
            commandSequence[index] = receivedChar - '0';
            index++;
        }
    }
}

void executeCommandSequence() {
    if (currentCommandIndex < sizeof(commandSequence) / sizeof(commandSequence[0])) {
        switch (commandSequence[currentCommandIndex]) {
            case 0:
                executeForward();
                Serial.println("Foward_Exe");
                Serial.println(currentCommandIndex);
                break;
            case 1:
                executeLeft();
                Serial.println("Left_exe");
                Serial.println(currentCommandIndex);
                break;
            case 2:
                executeRight();
                Serial.println("Right_exe");
                Serial.println(currentCommandIndex);
                break;
        }
        currentCommandIndex++; // Cập nhật chỉ số lệnh để lần kích hoạt tiếp theo thực hiện lệnh kế tiếp
    }
    delay(500); // Delay sau khi thực hiện lệnh
}


void straightStick() {
    if (digitalRead(Sensor1) == 0 || (digitalRead(Sensor2) == 0 && digitalRead(Sensor4) != 0)) {
        Turn_left();
        Serial.println("Left");
        
    }
    if (digitalRead(Sensor5) == 0 || (digitalRead(Sensor4) == 0 && digitalRead(Sensor2) != 0)) {
        Turn_right();
        Serial.println("Right");
        
    }
    if ((digitalRead(Sensor1) == 0 && digitalRead(Sensor2) == 1 && digitalRead(Sensor3) == 1 &&
         digitalRead(Sensor4) == 1 && digitalRead(Sensor5) == 0)) {
        Serial.println("Stop");
        
    } else if ((digitalRead(Sensor1) == 1 && digitalRead(Sensor2) == 1 && digitalRead(Sensor3) == 0 &&
                digitalRead(Sensor4) == 1 && digitalRead(Sensor5) == 1) ||
               (digitalRead(Sensor1) == 1 && digitalRead(Sensor2) == 0 && digitalRead(Sensor3) == 0 &&
                digitalRead(Sensor4) == 0 && digitalRead(Sensor5) == 1)) {
        forward();
        Serial.println("Forward");
        
    }
}

void car_stop() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    
}

void forward() {
    analogWrite(ENA, EN);
    analogWrite(ENB, EN);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    
}


void straight() {

    analogWrite(ENA, EN);
    analogWrite(ENB, EN);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    
}

void Turn_right() {
    analogWrite(ENA, EN_TURN);
    analogWrite(ENB, EN);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    
}

void Turn_left() {
    analogWrite(ENA, EN);
    analogWrite(ENB, EN_TURN);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    
}

void executeForward() {
    // Write the code for forward motion
    // Example:
    forward();
    
}

void executeLeft() {
     analogWrite(ENA, EN);
    analogWrite(ENB, EN_Exe);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    
}

void executeRight() {
    analogWrite(ENA, EN_Exe);
    analogWrite(ENB, EN);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    
}