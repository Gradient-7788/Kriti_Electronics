#include <Servo.h>

const int sensorPin = A0;   // Rain sensor analog pin
const int servoPin = 9;     // Servo control pin
const int espPin = 7;       // Pin receiving HIGH/LOW from ESP8266
const int controlOutPin = 6; // GPIO to be controlled by ESP signal

Servo myServo;

void setup() {
    myServo.attach(servoPin);
    pinMode(espPin, INPUT);
    pinMode(controlOutPin, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    int espState = digitalRead(espPin);  // Read ESP8266 signal
    int sensorValue = analogRead(sensorPin);
    float voltage = (sensorValue / 1023.0) * 5.0; // Convert to voltage
    int angle = 0;  // Default position

    // Control the Arduino GPIO based on ESP8266 state
    if (espState == HIGH) {
        digitalWrite(controlOutPin, HIGH);
    } else {
        digitalWrite(controlOutPin, LOW);
    }

    // Servo control using rain sensor 
    if (voltage <= 1.4) {
        angle = 180;  // Level 4
    } else if (voltage <= 2.0) {
        angle = 120;  // Level 3
    } else if (voltage <= 2.5) {
        angle = 60;   // Level 2
    } else if (voltage <= 3.0) {
        angle = 0;    // Level 1
    }

    myServo.write(angle);

    // Debugging info
    Serial.print("ESP State: "); Serial.print(espState);
    Serial.print(" | Voltage: "); Serial.print(voltage);
    Serial.print("V | Servo Angle: "); Serial.print(angle);
    Serial.print(" | Control Output: "); Serial.println(digitalRead(controlOutPin));

    delay(500);
}
