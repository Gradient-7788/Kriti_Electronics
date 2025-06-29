#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
const int controlPin = 2;  // GPIO2 connected to Arduino

void handleRoot() {
    server.send(200, "text/html",
        "<h2>ESP8266 Pin Control</h2>"
        "<a href='/HIGH'><button style='font-size:20px;padding:10px;'>Turn ON</button></a> "
        "<a href='/LOW'><button style='font-size:20px;padding:10px;'>Turn OFF</button></a>");
}

void handleHigh() {
    digitalWrite(controlPin, HIGH);
    server.send(200, "text/plain", "ESP Pin is HIGH");
}

void handleLow() {
    digitalWrite(controlPin, LOW);
    server.send(200, "text/plain", "ESP Pin is LOW");
}

void setup() {
    Serial.begin(115200);

    // Create ESP8266 WiFi Hotspot
    WiFi.softAP("ESP8266_Hotspot", "12345678");  // SSID: ESP8266_Hotspot, Password: 12345678

    Serial.println("AP Started! Connect to WiFi: ESP8266_Hotspot, Password: 12345678");

    IPAddress IP = WiFi.softAPIP();
    Serial.print("ESP8266 AP IP Address: ");
    Serial.println(IP);  // Print the local IP (192.168.4.1)

    pinMode(controlPin, OUTPUT);
    digitalWrite(controlPin, LOW);

    server.on("/", handleRoot);
    server.on("/HIGH", handleHigh);
    server.on("/LOW", handleLow);

    server.begin();
}

void loop() {
    server.handleClient();
}
