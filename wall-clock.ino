// secrets
#include "arduino_secrets.h"
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

// 8x32 Panel Output
#include <SPI.h>
#include <Adafruit_GFX.h> // --> https://github.com/adafruit/Adafruit-GFX-Library
#include <Max72xxPanel.h> // --> https://github.com/markruys/arduino-Max72xxPanel

// Wifi
#include <WiFiManager.h>
#include <ESP8266WiFi.h>


const int pinCS = D6;
int displayIntensity = 1;  //(This can be set from 0 - 15)
const int numberOfHorizontalDisplays = 4; // default 4 for standard 4 x 1 display Max size of 16
const int numberOfVerticalDisplays = 1; // default 1 for a single row height

String display_text = "banana";

void setup() {
  Serial.begin(9600);
    Serial.println();
    Serial.println("Begin");
    
  // 8x32 display begin
  Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);
  
  matrix.setIntensity(0); // Use a value between 0 and 15 for brightness

  int maxPos = numberOfHorizontalDisplays * numberOfVerticalDisplays;
  for (int i = 0; i < maxPos; i++) {
    matrix.setRotation(i, 3);
    matrix.setPosition(i, maxPos - i - 1, 0);
  }
 
  matrix.fillScreen(LOW); 
  matrix.setCursor(0, 1);
  matrix.print(display_text);
  matrix.write();
  // 8x32 display end

 //wifi begin
  WiFiManager wifiManager;
  wifiManager.autoConnect(ssid, pass);

  //don't need these - WifiManager provides verbose in Serial
  //Serial.write("Connected at ");
  //Serial.println(WiFi.localIP().toString());  
 //wifi end

 //time begin
 //time end


}

void loop(){
  int i = 0;
  Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

  matrix.setIntensity(0); // Use a value between 0 and 15 for brightness

  int maxPos = numberOfHorizontalDisplays * numberOfVerticalDisplays;
  for (int i = 0; i < maxPos; i++) {
    matrix.setRotation(i, 3);
    matrix.setPosition(i, maxPos - i - 1, 0);
  }

//simple scroll implementation
  while (i < 32){
    matrix.fillScreen(LOW); 
    matrix.setCursor(i, 0);
    matrix.print(display_text);
    matrix.write();
    delay(250);
    i++;
  }

  delay(500);
}
