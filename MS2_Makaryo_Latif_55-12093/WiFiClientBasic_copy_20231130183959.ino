#include <ESP8266WiFi.h>
#include <WiFiClient.h>
 
const char* ssid = "Makario's Galaxy S21 Ultra 5G";
const char* password =  "dbxj7786";
 
const uint16_t port = 5015;
const char * host = "192.168.34.41";
const int outputpin= A0;
 
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
    Serial.print("connecting to ");
    Serial.print(host);
    Serial.print(':');
    Serial.println(port);
    WiFiClient client;
 
    if (!client.connect(host, port)) {
 
        Serial.println("Connection to host failed");
        Serial.println("wait 10 sec...");
        delay(1000);
        return;
    }
 
    Serial.println("Connected to server successful!");
 
    int analogValue = analogRead(outputpin);
    float millivolts = (analogValue/1024.0) * 3300; //3300 is the voltage provided by NodeMCU
    float celsius = millivolts/10;
    Serial.print("in DegreeC=   ");
    Serial.println(celsius);

    //---------- Here is the calculation for Fahrenheit ----------//

    float fahrenheit = ((celsius * 9)/5 + 32);
    Serial.print(" in Farenheit=   ");
    Serial.println(fahrenheit);

    Serial.println("receiving from remote server");
    String requestBody = String(celsius);
    client.println(requestBody);
    String line = client.readStringUntil('\r');
  
    Serial.println(line);
 
    Serial.println("Disconnecting...");
    client.stop();
 
    delay(10000);
}

