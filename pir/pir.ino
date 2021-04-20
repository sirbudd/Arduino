#include "LedStripController.h"
#include "24KeysCodes.h"

#define RGB_CHANNEL_0 13        // the pin that the LED is atteched to
int PIR = 3;              // the pin that the sensor is atteched to


LedStripController led_channel_0;
void setup() {
  led_channel_0.begin(RGB_CHANNEL_0);  // initalize LED as an output
  pinMode(PIR, INPUT);    // initialize sensor as an input
  Serial.begin(9600);     // initialize serial

}

void loop(){
  if (digitalRead(PIR) == HIGH) { 
    led_channel_0.writeCommand(IR_G);// check if the sensor is HIGH 
    Serial.println("Motion detected!");
    delay(1000);                    // delay 1000 milliseconds 
  } 
  else {      
    digitalWrite(13, LOW);// turn LED OFF
    Serial.println("Motion stopped!");
    delay(100);                   // delay 100 milliseconds
  }
}
