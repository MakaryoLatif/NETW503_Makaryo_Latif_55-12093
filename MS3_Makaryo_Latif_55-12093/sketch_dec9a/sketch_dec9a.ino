#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingsBoard.h>

const char* ssid = "Makario's Galaxy S21 Ultra 5G";
const char* password = "dbxj7786";
const char* tbServer = "thingsboard.cloud";
const char* tbToken = "z2o85sfvoghk2druncjf";

WiFiClient wifiClient;
ThingsBoard tb(wifiClient);

const int outputPin = A0;

void setup()
{
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }

  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  if (!tb.connected()) {
    Serial.println("Connecting to ThingsBoard...");
    if (tb.connect(tbServer, tbToken)) {
      Serial.println("Connected!");
    } else {
      Serial.println("Failed to connect. Retry in 5 seconds...");
      delay(5000);
      return;
    }
  }

  int analogValue = analogRead(outputPin);
  float millivolts = (analogValue / 1024.0) * 3300; // 3300 is the voltage provided by NodeMCU
  float celsius = millivolts / 10;
  Serial.print("Temperature in DegreeC: ");
  Serial.println(celsius);

  float fahrenheit = ((celsius * 9) / 5) + 32;
  Serial.print("Temperature in Fahrenheit: ");
  Serial.println(fahrenheit);

  tb.sendTelemetryFloat("temperature", celsius);

  delay(10000);
}
