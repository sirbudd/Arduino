#include <ESP8266WiFi.h>
#include <DHT.h> 
String apiKey = "0QXH37SSI9BIS6C1";     //  Enter your Write API key from ThingSpeak
 
const char *ssid =  "FalconVille";     // replace with your wifi ssid and wpa2 key
const char *pass =  "Pa55wordfalcon!";
const char* server = "api.thingspeak.com";
 
#define DHTPIN D5          //pin where the dht11 is connected
#define MQPIN A0

DHT dht(DHTPIN, DHT11);

int sensorValue;
int digitalValue;
 
WiFiClient client;
 
void setup() 
{
       Serial.begin(9600);
       delay(10);
       dht.begin();
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{
  
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      float a = analogRead(0);
      sensorValue = analogRead(0); // read analog input pin 0

      digitalValue = digitalRead(2); 
      if(sensorValue>400)
      {
        digitalWrite(A0, HIGH);
      }
      else
      digitalWrite(A0, LOW);
      Serial.print(F("Air Quality : "));
      Serial.println(sensorValue, DEC); // prints the value read
      //Serial.println(digitalValue, DEC);
      
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
 
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr +="&field3=";
                             postStr += String(a);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}
