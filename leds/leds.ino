#include "LedStripController.h"
#include "24KeysCodes.h"

#define RGB_CHANNEL_0 13

LedStripController led_channel_0;
void setup() 
{
   // Initialise the output channels.
   led_channel_0.begin(RGB_CHANNEL_0);
}

void loop() 
{
   // Write commands to the LED strip controller.
   led_channel_0.writeCommand(IR_G);
   delay(1000);
   led_channel_0.writeCommand(IR_R);
   delay(1000);
}
