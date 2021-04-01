//trying to use a MQTT Server to send info to a Raspberry PI

#include "DHT.h"
#include "PubSubClient.h" // Connect and publish to the MQTT broker
#include <ESP8266WiFi.h>
const char* ssid     = "FalconVille";      // SSID of local network
const char* password = "Pa55wordfalcon!";   // Password on network
String result;
String motion ;

void setup() 
{
  pinMode(D5, INPUT);
  delay(2000);
  Serial.begin(9600);
  WiFi.hostname("ESP8266MotionSensor"); //This changes the hostname of the ESP8266 to display neatly on the network esp on router.
  WiFi.begin(ssid, password);
}

void loop() 
{
  if(digitalRead(D5)== HIGH)
  {
   motion = digitalRead(D5); //PIR sensor pin
   Serial.println("Alarm detected!"); //Send things to serial for info
   Serial.print("motion ");
   Serial.println(motion);
   delay(1000);
  } 
  else 
  {
    Serial.println("no trigger"); //enable for debugging of no event being triggered
  }
}
