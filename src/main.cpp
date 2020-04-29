#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "certs.h"
//#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <SPI.h>
//#include <DHT_U.h>
#include <ArduinoJson.h>

#define DHT_TYPE DHT11
#define DHT_PIN 22
 
const char *SSID = "SSID"; // your custom WiFi SSID
const char *PWD = "PASSWORD"; // your WiFI Password

#define AWS_IOT_ENDPOINT "AWS_IOT_ENDPOINT" // your AWS IOT Endpoint

#define DEVICE_NAME "DEVICE_NAME" // your device name
 
WiFiClientSecure secureClient = WiFiClientSecure();
PubSubClient mqttClient(secureClient);

DHT dht(DHT_PIN, DHT_TYPE);
 
void connectToWiFi() 
{
  Serial.print("Connecting to ");
  Serial.println(SSID);
  WiFi.begin(SSID, PWD); 
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500); 
  }
 
  Serial.print("Connected to ");
  Serial.println(SSID);
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
}
 
void connectToAWS() 
{
  mqttClient.setServer(AWS_IOT_ENDPOINT, 8883);
  secureClient.setCACert(AWS_CERT_CA);
  secureClient.setCertificate(AWS_CERT_CRT);
  secureClient.setPrivateKey(AWS_CERT_PRIVATE);
 
  Serial.println("Connecting to MQTT....");
 
  mqttClient.connect(DEVICE_NAME);
   
  while (!mqttClient.connected()) 
  {
    Serial.println("Connecting to MQTT....Retry");
    mqttClient.connect(DEVICE_NAME);
    delay(5000);
  }
  
  Serial.println("MQTT Connected");
}
 
void setup() 
{
  Serial.begin(9600);
  connectToWiFi();
  connectToAWS();

  dht.begin();
}

void loop() 
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  // Compute the hit Index using celsius
  float heatIndex = dht.computeHeatIndex(temperature, humidity, false);
 
  Serial.print("Temperature:");
  Serial.println(temperature);
  Serial.print("Humidity:");
  Serial.println(humidity);
  Serial.print("Heat Index:");
  Serial.println(heatIndex);
  
  StaticJsonDocument<128> jsonDoc;
  JsonObject eventDoc = jsonDoc.createNestedObject("event");
  eventDoc["temp"] = temperature;
  eventDoc["hum"] = humidity;
  eventDoc["hi"] = heatIndex;
 
  char jsonBuffer[128];
 
  serializeJson(eventDoc, jsonBuffer);
  mqttClient.publish("mychannel/", jsonBuffer); // specify your custom channel name
  delay(10000);
}