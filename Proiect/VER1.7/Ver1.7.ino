#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "FalconVille";
const char* password = "Pa55wordfalcon!";
const char* mqtt_server = "192.168.50.125";// !!!! Raspberry Pi IP address !!!!
const int PirPin = D5; // LED connected to pin D5

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  pinMode(PirPin, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // ... and resubscribe
      client.subscribe("led_topic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    value=digitalRead(D5);
    if(value == HIGH)
    {
      snprintf (msg, 75, "%ld", value);
      Serial.print("Publish message(HIGH): ");
      Serial.println(msg);
      client.publish("sensor_data", msg);
    }
    else if(value == LOW)
    {
      snprintf (msg, 75, "%ld", value);
      Serial.print("Publish message(LOW): ");
      Serial.println(msg);
      client.publish("sensor_data", msg);
    }
    
  }
  /**
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
**/
  
}
