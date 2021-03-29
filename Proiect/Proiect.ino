#include <ESP8266WiFi.h>
const char* ssid     = "FalconVille";      // SSID of local network
const char* password = "Pa55wordfalcon!";   // Password on network
String result;
String motion ;

void setup() 
{
  pinMode(D4, INPUT);
  delay(2000);
  Serial.begin(115200);
  WiFi.hostname("ESP8266MotionSensor"); //This changes the hostname of the ESP8266 to display neatly on the network esp on router.
  WiFi.begin(ssid, password);
}

void ifttt() //Wifi connection and send all the data to IFTTT
{
  const char host[ ]        = "maker.ifttt.com";          // maker channel of IFTTT
  const char trigger[ ]     = "Motan";                   //name of the trigger you would like to send to IFTTT
  const char APIKey[ ]      = "cJ9QhIWnyX9nbKMomkE7L1gzvUgS7ub9ARZXlJJ6XBZ";      //Your maker key for Webhooks on IFTTT
  Serial.print("Connect to: ");
  Serial.println(host);
  // WiFiClient to make HTTP connection
  WiFiClient client;
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
  client.stop();  //disconnect
  delay (20000); //stop email/notif spam
 }
  
void loop() //Where stuffz happens
{
 if(digitalRead(D4)== HIGH)  // ||digitalRead(D7)== HIGH) Removed MQ2 or condition
  {
   motion = digitalRead(D4); //PIR sensor pin
   Serial.println("Alarm detected!"); //Send things to serial for handy dandy info
   Serial.print("motion ");
   Serial.println(motion);

   ifttt(); //Tell IFTTT that intruder detected
  } 
  else 
  {
    Serial.println("no trigger"); //enable for debugging of no event being triggered
  }
}
