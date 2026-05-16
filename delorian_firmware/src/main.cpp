#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "Wasabi";
const char* password = "Atehortua";
const int serverPort = 8080;

WiFiServer server(serverPort);
WiFiClient client;

void setup() {

Serial.begin(115200);
  WiFi.begin(ssid,password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
Serial.println("Conectado");
Serial.print("IP Adress: ");
Serial.println(WiFi.localIP());
server.begin();
Serial.println("Servidor comenzado");

pinMode(34, OUTPUT); //Puerto de D7-D4
pinMode(35, OUTPUT);
pinMode(32, OUTPUT);
pinMode(33, OUTPUT);

}

void loop() {

    if (!client.connected()) {
    client = server.available();

        if (client) {
            Serial.println("Cliente conectado");
        }
    }

    if (client && client.available()) {

        int data = client.readStringUntil('\n').toInt();
        Serial.print("Recibido: ");
        Serial.println(data);

        if (data == 1) {
            digitalWrite(34, HIGH);
            digitalWrite(35, LOW);
            digitalWrite(32, HIGH);
            digitalWrite(33, LOW);
        }

        else if (data == 0) {
            digitalWrite(34, LOW);
            digitalWrite(35, LOW);
            digitalWrite(32, LOW);
            digitalWrite(33, LOW);
        }

        delay(10);
    }
}