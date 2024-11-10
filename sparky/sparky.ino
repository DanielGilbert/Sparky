/*####################################################
||                                                ||
||                     Sparky                     ||
||          Your friendly desk companion          ||
||               by Daniel Gilbert                ||
||                      2024                      ||
||                                                ||
||    https://github.com/DanielGilbert/Sparky     ||
||                                                ||
||                License: GPL-3.0                ||
||                                                ||
####################################################*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 132 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

#include <RoboEyes/FluxGarage_RoboEyes.h>
roboEyes roboEyes; // create RoboEyes instance
unsigned long eventTimer; // will save the timestamps
bool event1wasPlayed = 0; // flag variables
bool event2wasPlayed = 0;
bool event3wasPlayed = 0;


void setup() {
  display.begin(0x3c);
  display.setContrast(0);

  roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 120); // screen-width, screen-height, max framerate

  // Define some automated eyes behaviour
  roboEyes.setPosition(DEFAULT); // eye position should be middle center
  roboEyes.close(); // start with closed eyes 
  
  eventTimer = millis(); // start event timer from here
} // end of setup

void loop() {
 roboEyes.drawEyes(); // update eyes drawings

   // LOOPED ANIMATION SEQUENCE
  // Do once after defined number of milliseconds
  if(millis() >= eventTimer+2000 && event1wasPlayed == 0){
    event1wasPlayed = 1; // flag variable to make sure the event will only be handled once
    roboEyes.open(); // open eyes 
  }
  // Do once after defined number of milliseconds
  if(millis() >= eventTimer+4000 && event2wasPlayed == 0){
    event2wasPlayed = 1; // flag variable to make sure the event will only be handled once
    roboEyes.setMood(HAPPY);
    roboEyes.anim_laugh();
    //roboEyes.anim_confused();
  }
  // Do once after defined number of milliseconds
  if(millis() >= eventTimer+6000 && event3wasPlayed == 0){
    event3wasPlayed = 1; // flag variable to make sure the event will only be handled once
    roboEyes.setMood(DEFAULT);
    roboEyes.setCuriosity(ON);
    roboEyes.setIdleMode(ON, 2, 2);
  }
  // Do once after defined number of milliseconds, then reset timer and flags to restart the whole animation sequence
  if(millis() >= eventTimer + 25000){
    roboEyes.setCuriosity(OFF);
    roboEyes.setIdleMode(OFF);
    roboEyes.setMood(DEFAULT);
    roboEyes.setPosition(DEFAULT);
    roboEyes.close(); // close eyes again

    // Reset the timer and the event flags to restart the whole "complex animation loop"
    eventTimer = millis(); // reset timer
    event1wasPlayed = 0; // reset flags
    event2wasPlayed = 0;
    event3wasPlayed = 0;
  }
  // END OF LOOPED ANIMATION SEQUENCE
}
