//trying to use a MQTT Server to send info to a Raspberry PI

#include "DHT.h"
#include "PubSubClient.h" // Connect and publish to the MQTT broker
#include <ESP8266WiFi.h>
const char* ssid     = "FalconVille";      // SSID of local network
const char* password = "Pa55wordfalcon!";   // Password on network
String result;
String motion ;


// MQTT
const char* mqtt_server = "192.168.50.125 ";  // IP of the MQTT broker
const char* humidity_topic = "/home/pi/Arduino";
const char* mqtt_username = "Falcon"; // MQTT username
const char* mqtt_password = "pass1"; // MQTT password
const char* clientID = "Client"; // MQTT client ID

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
// 1883 is the listener port for the Broker
PubSubClient client(mqtt_server, 1883, wifiClient); 

// Custom function to connect to the MQTT broker via WiFi
void connect_MQTT(){
  Serial.print("Connecting to ");
  Serial.println(ssid);
}

  // Connect to the WiFi
//WiFi.begin(ssid, wifi_password);

  // Wait until the connection has been confirmed before continuing
while (WiFi.status() != WL_CONNECTED) 
{
  delay(500);
  Serial.print(".");
}

  // Debugging - Output the IP Address of the ESP8266
Serial.println("WiFi connected");
Serial.print("IP address: ");
Serial.println(WiFi.localIP());

  // Connect to MQTT Broker
  // client.connect returns a boolean value to let us know if the connection was successful.
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }
}


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
  connect_MQTT();
  if(digitalRead(D5)== HIGH)
  {
   motion = digitalRead(D5); //PIR sensor pin
   Serial.println("Alarm detected!"); //Send things to serial for info
   Serial.print("motion ");
   Serial.println(motion);
   delay(5000);
  } 
  else 
  {
    Serial.println("no trigger"); //enable for debugging of no event being triggered
  }
}
