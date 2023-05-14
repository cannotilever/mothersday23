// mothers' day intro handheld board
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "wifi.h" //untracked file containing credentials

Adafruit_SSD1306 display(128, 64, &Wire, -1);
uint8_t LEDstage = 0;

#define LED1 18
#define LED2 5
#define LED3 19
#define LED4 17
#define LED5 16

int LEDlist[] = {LED1, LED2, LED3, LED4, LED5};

unsigned long peripheralTimer = 0;

void welcomeScreen(){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Happy Mother's Day!!!");
  display.setCursor(0, 20);
  display.println("Turn the knob when ready.");
  display.setCursor(20,50);
  display.print("[o] ------>");
  display.display();
}

void setup() {
    Serial.begin(115200);
  while (!Serial) {}
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("Display allocation failed");
    while(true) {Serial.println("Reset device.");}
  }
  display.display();
  delay(500);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
  display.setTextColor(WHITE);
  for (int i=0; i<5; i++){
    pinMode(LEDlist[i], OUTPUT);
  }
  welcomeScreen();
}

void mainScreen(int progress){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Progress: " + String(progress) + "/5");
  if (progress){
    display.setCursor(0, 25);
    display.println("Use the hints provided by the QR codes on your phone.");

  }
  else {
    display.setCursor(0, 17);
    display.println("First Hint:");
    display.setCursor(0,27);
    display.print("I contain waves but no water. I have a door & window but none may enter me.");
  }
  display.display();
}

void winScreen(){
  display.clearDisplay();
  display.setCursor(10, 0);
  display.println("You Win!!!");
  display.setCursor(0, 40);
  display.println("I love you mom, happy mother's day <3");
  display.display();
}

void updateLEDs(int progress){
  for (int i = 0; i<5; i++){
    digitalWrite(LEDlist[i], (i<progress));
  }
}

void LEDchase(){
  for (int i = 0; i<5; i++){
    digitalWrite(LEDlist[i], (i==LEDstage));
  }
  if (LEDstage++ > 4) LEDstage = 0;
}

void LEDexpand(){
  int mask;
  static int addVal;
  switch (LEDstage)
  {
  case 0:
    mask = 0x4;
    addVal = 1;
    break;
  case 1:
    mask = 0xA;
    break;
  case 2:
    mask = 0x11;
    break;  
  default:
    mask = 0;
    addVal = -1;
    break;
  }
  LEDstage += addVal;
  for (int i = 0; i<5; i++){
    digitalWrite(LEDlist[i],((1<<i)&mask));
  }
}

void loop() {
  static uint8_t mode = 0;
  static int stat = 0;
  // put your main code here, to run repeatedly:
  switch (mode){
    case 0:
      if (millis() - peripheralTimer > 150){
        peripheralTimer = millis();
        LEDchase();
        if (analogRead(34) > 2048) mode = 1;
      }
      break;
    
    case 1:
      if (millis() - peripheralTimer > 1500){
        HTTPClient http;
        http.begin("http://192.168.10.15/status");
        http.GET();
        stat = http.getString().toInt();
        http.end();
        updateLEDs(stat);
        mainScreen(stat);
        peripheralTimer = millis();
        if (stat == 5) {
          mode = 2;
          delay(2000);
          winScreen();
        }
      }
      break;
    
    case 2:
      if (millis() - peripheralTimer > 100){
        LEDexpand();
        peripheralTimer = millis();
      }
      break;

  }
  delay(10); 
}