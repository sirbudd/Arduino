#include <ESP8266WiFi.h>
const char* ssid     = "FalconVille";      // SSID of local network
const char* password = "Pa55wordfalcon!";   // Password on network
String result;
String smoke ;
String motion ;

void setup() 
{
  pinMode(D4, INPUT);
  pinMode(D7, INPUT);
  delay(2000);
  Serial.begin(115200);
  WiFi.hostname("ESP8266MotionSensor"); //This changes the hostname of the ESP8266 to display neatly on the network esp on router.
  WiFi.begin(ssid, password);
  
}

void ifttt() //Wifi connection and send all the data to IFTTT
{
  const char host[ ]        = "maker.ifttt.com";          // maker channel of IFTTT
  const char trigger[ ]     = "motion";                   //name of the trigger you would like to send to IFTTT
  const char APIKey[ ]      = "https://maker.ifttt.com/use/cJ9QhIWnyX9nbKMomkE7L1gzvUgS7ub9ARZXlJJ6XBZ";      //Your maker key for Webhooks on IFTTT
  Serial.print("Connect to: ");
  Serial.println(host);
  // WiFiClient to make HTTP connection
  BearSSL::WiFiClientSecure client;
  const int API_TIMEOUT = 10000;
  client.setInsecure();
  client.setTimeout(API_TIMEOUT);
  
  if (!client.connect(host, 80)) {
    Serial.println("connection failed");
    return;
    }

// Build URL
  String url = String("/trigger/") + trigger + String("/with/key/") + APIKey;
  Serial.print("Requesting URL: ");
  Serial.println(url);

// Send request to IFTTT
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n"); 
  //FYI rn rn is just two new lines to comply with http format
   delay(20);

// Read all the lines of the reply from server and print them to Serial
  Serial.println("Respond:");
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
    }
  Serial.println();
  Serial.println("closing connection");
  Serial.println(); //space things our in serial monitor for purdy
  Serial.println();
  client.stop();  //V5 added this to disconnect
  delay (20000); //This delay here just to stop spamming of emails- should be polished to a better method/location
 }
  
void loop() //Where stuffz happens
{
 if(digitalRead(D4)== HIGH)  // ||digitalRead(D7)== HIGH) Removed MQ2 or condition
  {
   motion = digitalRead(D3); //PIR sensor pin
   smoke = digitalRead(D7);  //MQ2 smoke sensor pin
   Serial.println("Alarm detected!"); //Send things to serial for handy dandy info
   //Serial.print("motion ");
   Serial.println(motion);
   Serial.print("smoke ");
   Serial.println(smoke);
   ifttt(); //Tell IFTTT that intruder detected
  } 
  else 
  {
    //Serial.println("no trigger"); //enable for debugging of no event being triggered
  }
}
