#include "DHT.h"

#define MQPIN A0 // Digital pin connected to the MQ-135 sensor
#define DHTPIN D5     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11 /what type of sensor we have

DHT dht(DHTPIN, DHTTYPE);

int sensorValue;
int digitalValue;

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT11 test!"));
  dht.begin();
}

void loop() {
  delay(1000);
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  /**
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  **/
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

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(F("Heat index: "));
  Serial.print(hic);
  Serial.println(F("°C "));

}
