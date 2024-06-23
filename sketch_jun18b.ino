
#define BLYNK_TEMPLATE_ID "TMPL4vdcxUqfr"
#define BLYNK_TEMPLATE_NAME "Proiect Desenare"
#define BLYNK_AUTH_TOKEN "m5QVJ5rMzzuAlNCTJYTQctA-l7qkYH7a"

#include "Drawings.hpp"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
// Id of the drawing that is to be sent
int SelectedDrawing;
// Flag to decide when to start drawing
int StartDrawing;
int CanDraw;
// login info
String ssid = "iPhone - Tiberiu";
String pass = "abc123-nao";
// Strings to hold the Gcode for each drawing

// Init function specific to arduino
void setup() {
  // Connect to WiFi and blynk server
  Blynk.begin(BLYNK_AUTH_TOKEN, "ssid","pass");
  delay(1000);
  // Start the Uart channel to send to arduino
  Serial2.begin(115200);
}

// put your main code here, to run repeatedly:
void loop() {
  // Run Blynk code
  Blynk.run();
  // If the user wants to start drawing
  if (StartDrawing){
    // lock the start drawing button untill drawing is finnished
    CanDraw = 0;
    // reset variable so that the picture is not drawn twice
    StartDrawing = 0;
    // update UI, led and reset start drawing button
    Blynk.virtualWrite(V1,CanDraw);
    Blynk.virtualWrite(V0,0);
    // send the gcode over uart to the arduino based on the selected drawing 
    switch(SelectedDrawing){
      case 0:{
        Serial2.println(Draw0);
        break;
      }
      case 1 :{
        Serial2.println(Draw1);
        break;
      }
      case 2:{
        Serial2.println(Draw2);
        break;
      }
      case 3:{
        Serial2.println(Draw3);
        break;
      }
      case 4:{
        Serial2.println(Draw4);
        break;
      }
    // unlock the start drawing button
    CanDraw = 1;
    // update UI for the led
    Blynk.virtualWrite(V1,CanDraw);
    }
  }

}
// this executes when the select drawing slider is released
BLYNK_WRITE(V0){
  // get the desired drawing form the user 
SelectedDrawing = param.asInt();
}
// this executes when the user presses the start drawing button
BLYNK_WRITE(V2){
  // if the eggbot is not allready drawing something
  if (CanDraw){
    // start drawing
    StartDrawing = param.asInt();
  }
}