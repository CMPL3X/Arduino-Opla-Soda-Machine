#include "arduino_secrets.h"
#include <Arduino_MKRIoTCarrier.h>
#include <Arduino_OplaUI.h>
#include <Arduino_MKRIoTCarrier_Buzzer.h>
#include <Arduino_MKRIoTCarrier_Qtouch.h>
#include <Arduino_MKRIoTCarrier_Relay.h>
#include "thingProperties.h"
#include <Adafruit_NeoPixel.h>

// SETTINGS ///////////////////////////////////////////////////////////////////////////////////////////////////

int CupSizeHalfM1 = 9990; // YOU HAVE TO CHANGE THIS!
int CupSizeFullM1 = 14000; // YOU HAVE TO CHANGE THIS!

int CupSizeHalfM2 = 9990; // YOU HAVE TO CHANGE THIS!
int CupSizeFullM2 = 14500; // YOU HAVE TO CHANGE THIS!

bool FakeStartup = true; // This is the fake "loading..." screen that pops up when pluged in. If true it will turn on at startup, if false it wont.

char Drink1[] = "Coca-Cola";
int Drink1Coordinates_X = 20;
int Drink1Coordinates_Y = 150;

int HomeScreenTextSize = 2; // 1 small    2 avrage    3 big

char Drink2[] = "Fanta";
int Drink2Coordinates_X = 160;
int Drink2Coordinates_Y = 150;

int lightColor = 4; // 1 = Red   2 = Yellow    3 = Green   4 = Cyan (Recommended)    5 = Blue

#define PIN A5 // NEOPIXEL RING PIN

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

MKRIoTCarrier carrier;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

int Time1 = 0;
int i = 0;
int Po;
int sc = 0;
int v = 0;

const uint16_t  Black        = 0x0000;
const uint16_t  Blue         = 0x001F;
const uint16_t  Red          = 0xF800;
const uint16_t  Green        = 0x07E0;
const uint16_t  Cyan         = 0x07FF;
const uint16_t  Magenta      = 0xF81F;
const uint16_t  Yellow       = 0xFFE0;
const uint16_t  White        = 0xFFFF;

uint32_t StartupColor = carrier.leds.Color(255, 255, 255);
uint32_t LedsOff = carrier.leds.Color(0, 0, 0);

void setup() {
  CARRIER_CASE = true;
  
  carrier.begin();
  
  CARRIER_CASE = true; // CHANGE THIS (optional)
  
  strip.begin();
  strip.setBrightness(100);  // Lower brightness and save eyeballs!
  strip.show();
  
  Serial.begin(9600);
  delay(1500);
  
  initProperties();

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  carrier.display.setRotation(0);
  
  carrier.display.setTextSize(2);
  carrier.display.setTextColor(White);
  carrier.display.setCursor(85, 40);
  carrier.display.print("Smart");
  carrier.display.setCursor(50, 80);
  carrier.display.print("SodaMachine");
  carrier.display.setTextSize(3);
  carrier.display.setCursor(30, 150);
  carrier.display.print("Loading...");
  carrier.leds.show();
  carrier.leds.setBrightness(85);
  
  if (FakeStartup == true)  {
    while (i <= 3) {
      strip.setPixelColor(0, StartupColor);
      strip.show();
      strip.setPixelColor(1, StartupColor);
      strip.show();
      strip.setPixelColor(2, StartupColor);
      strip.show();
      strip.setPixelColor(3, StartupColor);
      strip.show();
      carrier.leds.setPixelColor(0, StartupColor);
      carrier.leds.show();
      delay(100);
      strip.setPixelColor(4, StartupColor);
      strip.show();
      strip.setPixelColor(5, StartupColor);
      strip.show();
      strip.setPixelColor(6, StartupColor);
      strip.show();
      carrier.leds.setPixelColor(1, StartupColor);
      carrier.leds.show();
      delay(100);
      strip.setPixelColor(7, StartupColor);
      strip.show();
      strip.setPixelColor(8, StartupColor);
      strip.show();
      strip.setPixelColor(9, StartupColor);
      strip.show();
      carrier.leds.setPixelColor(2, StartupColor);
      carrier.leds.show();
      delay(100);
      strip.setPixelColor(10, StartupColor);
      strip.show();
      strip.setPixelColor(11, StartupColor);
      strip.show();
      strip.setPixelColor(12, StartupColor);
      strip.show();
      carrier.leds.setPixelColor(3, StartupColor);
      carrier.leds.show();
      delay(100);
      strip.setPixelColor(13, StartupColor);
      strip.show();
      strip.setPixelColor(14, StartupColor);
      strip.show();
      strip.setPixelColor(15, StartupColor);
      strip.show();
      strip.setPixelColor(16, StartupColor);
      strip.show();
      carrier.leds.setPixelColor(4, StartupColor);
      carrier.leds.show();
      delay(500);
      carrier.leds.setPixelColor(0, LedsOff);
      carrier.leds.show();
      strip.setPixelColor(0, StartupColor);
      strip.show();
      strip.setPixelColor(1, LedsOff);
      strip.show();
      strip.setPixelColor(2, LedsOff);
      strip.show();
      strip.setPixelColor(3, LedsOff);
      strip.show();
      delay(100);
      carrier.leds.setPixelColor(1, LedsOff);
      carrier.leds.show();
      strip.setPixelColor(4, LedsOff);
      strip.show();
      strip.setPixelColor(5, LedsOff);
      strip.show();
      strip.setPixelColor(6, LedsOff);
      strip.show();
      delay(100);
      carrier.leds.setPixelColor(2, LedsOff);
      carrier.leds.show();
      strip.setPixelColor(7, LedsOff);
      strip.show();
      strip.setPixelColor(8, LedsOff);
      strip.show();
      strip.setPixelColor(9, LedsOff);
      strip.show();
      delay(100);
      carrier.leds.setPixelColor(3, LedsOff);
      carrier.leds.show();
      strip.setPixelColor(10, LedsOff);
      strip.show();
      strip.setPixelColor(11, LedsOff);
      strip.show();
      strip.setPixelColor(12, LedsOff);
      strip.show();
      delay(100);
      carrier.leds.setPixelColor(4, LedsOff);
      carrier.leds.show();
      strip.setPixelColor(13, LedsOff);
      strip.show();
      strip.setPixelColor(14, LedsOff);
      strip.show();
      strip.setPixelColor(15, LedsOff);
      strip.show();
      strip.setPixelColor(16, LedsOff);
      strip.show();
      delay(100);
      i++;
    }
  }

  carrier.display.fillScreen(Black);
  MainScreen();
  
  if (lightColor == 1){
    AllLeds(255, 0, 0);
    AllPixels(255, 0, 0);
  }
  if (lightColor == 2){
    AllLeds(255, 255, 0);
    AllPixels(255, 255, 0);
  }
  if (lightColor == 3){
    AllLeds(0, 255, 0);
    AllPixels(0, 255, 0);
  }
  if (lightColor == 4){
    AllLeds(0, 251, 255);
    AllPixels(0, 251, 255);
  }
  if (lightColor == 5){
    AllLeds(0, 0, 255);
    AllPixels(0, 0, 255);
  }

  lights = 1;
  
  counter = 0;
  
}


void loop() {
  ArduinoCloud.update();
  CheckBt0();
  CheckBt2();
  CheckBt4();

}

void onColorChangeChange()  {
  if (colorChange == true){
    carrier.Buzzer.sound(4000);
    delay(200);
    carrier.Buzzer.noSound();
    ColorChangeScreen();
    sc = 0;
    while (sc == 0){
      carrier.Buttons.update();
      if (carrier.Buttons.onTouchDown(TOUCH0)) {
        carrier.Buzzer.sound(4000);
        delay(200);
        carrier.Buzzer.noSound();
        lightColor = 1;
        AllLeds(255, 0, 0);
        AllPixels(255, 0, 0);
        sc++;
        MainScreen();
      }
      if (carrier.Buttons.onTouchDown(TOUCH1)) {
        carrier.Buzzer.sound(4000);
        delay(200);
        carrier.Buzzer.noSound();
        lightColor = 2;
        AllLeds(255, 255, 0);
        AllPixels(255, 255, 0);
        sc++;
        MainScreen();
      }
      if (carrier.Buttons.onTouchDown(TOUCH2)) {
        carrier.Buzzer.sound(4000);
        delay(200);
        carrier.Buzzer.noSound();
        lightColor = 3;
        AllLeds(0, 255, 0);
        AllPixels(0, 255, 0);
        sc++;
        MainScreen();
      }
      if (carrier.Buttons.onTouchDown(TOUCH3)) {
        carrier.Buzzer.sound(4000);
        delay(200);
        carrier.Buzzer.noSound();
        lightColor = 4;
        AllLeds(0, 251, 255);
        AllPixels(0, 251, 255);
        sc++;
        MainScreen();
      }
      if (carrier.Buttons.onTouchDown(TOUCH4)) {
        carrier.Buzzer.sound(4000);
        delay(200);
        carrier.Buzzer.noSound();
        lightColor = 5;
        AllLeds(0, 0, 255);
        AllPixels(0, 0, 255);
        sc++;
        MainScreen();
      }
    }
  }
}

void ColorChangeScreen(){
  carrier.leds.setBrightness(50);
  carrier.leds.setPixelColor(0, 0, 255, 0);
  carrier.leds.setPixelColor(1, 255, 255, 0);
  carrier.leds.setPixelColor(2, 255, 0, 0);
  carrier.leds.setPixelColor(3, 255, 0, 255);
  carrier.leds.setPixelColor(4, 0, 0, 255);
  carrier.leds.show();
  carrier.display.fillScreen(Black);
  carrier.display.setTextColor(Red);
  carrier.display.setTextSize(2);
  carrier.display.setCursor(30, 155);
  carrier.display.print("Red");
  carrier.display.setTextColor(Yellow);
  carrier.display.setCursor(35, 45);
  carrier.display.print("Yellow");
  carrier.display.setTextColor(Green);
  carrier.display.setCursor(85, 15);
  carrier.display.print("Green");
  carrier.display.setTextColor(Cyan);
  carrier.display.setCursor(150, 45);
  carrier.display.print("Cyan");
  carrier.display.setTextColor(Blue);
  carrier.display.setCursor(160, 155);
  carrier.display.print("Blue");
  
}

void onPumpTestChange()  {
  carrier.Buzzer.sound(800);
  delay(200);
  carrier.Buzzer.noSound();
  carrier.Buzzer.sound(5000);
  delay(200);
  carrier.Buzzer.noSound();
  if (pumpTest == true){
    carrier.display.fillScreen(Red);
    carrier.display.setTextColor(Black);
    carrier.display.setTextSize(3);
    carrier.display.setCursor(40, 100);
    carrier.display.print("Pump Test");
    AllLeds(240, 0, 0);
    AllPixels(240, 0, 0);
    carrier.Relay1.open();
    carrier.Relay2.open();
  }
  if (pumpTest == false){
    carrier.Relay1.close();
    carrier.Relay2.close();
    MainScreen();
    if (lights == 0) {
      AllLeds(0, 0, 0);
      AllPixels(0, 0, 0);
    }
    else {
      if (lightColor == 1){
        AllLeds(255, 0, 0);
        AllPixels(255, 0, 0);
      }
      if (lightColor == 2){
        AllLeds(255, 255, 0);
        AllPixels(255, 255, 0);
      }
      if (lightColor == 3){
        AllLeds(0, 255, 0);
        AllPixels(0, 255, 0);
      }
      if (lightColor == 4){
        AllLeds(0, 251, 255);
        AllPixels(0, 251, 255);
      }
      if (lightColor == 5){
        AllLeds(0, 0, 255);
        AllPixels(0, 0, 255);
      }
    }
  }
}

void onDrink1HalfChange()  {
  if (drink1Half == true){
    Serial.print(" Drink 1H : true ");
    carrier.Buzzer.sound(4000);
    delay(200);
    carrier.Buzzer.noSound();
    MakingScreen();
    AllLeds(255, 255, 0);
    AllPixels(255, 255, 0);
    carrier.Relay2.open();
    delay(CupSizeHalfM1);
    carrier.Relay2.close();
    
    delay(CupSizeHalfM1 / 2 - 100);
    ArduinoCloud.update();
    delay(CupSizeHalfM1 / 2 - 100);
    
    ReadyScreen();
    AllLeds(0, 255, 0);
    AllPixels(0, 255, 0);
    carrier.Buzzer.sound(1000);
    delay(200);
    carrier.Buzzer.noSound();
    delay(100);
    carrier.Buzzer.sound(1500);
    delay(200);
    carrier.Buzzer.noSound();
    v++;
    MainScreen();
    if (lightColor == 1){
      AllLeds(255, 0, 0);
      AllPixels(255, 0, 0);
    }
    if (lightColor == 2){
      AllLeds(255, 255, 0);
      AllPixels(255, 255, 0);
    }
    if (lightColor == 3){
      AllLeds(0, 255, 0);
      AllPixels(0, 255, 0);
    }
    if (lightColor == 4){
      AllLeds(0, 251, 255);
      AllPixels(0, 251, 255);
    }
    if (lightColor == 5){
      AllLeds(0, 0, 255);
      AllPixels(0, 0, 255);
    }
    counter++;
  }
}

void onDrink2HalfChange()  {
  if (drink2Half == true){
    Serial.print(" Drink 2H : true ");
    carrier.Buzzer.sound(4000);
    delay(200);
    carrier.Buzzer.noSound();
    MakingScreen();
    AllLeds(255, 255, 0);
    AllPixels(255, 255, 0);
    carrier.Relay1.open();
    
    delay(CupSizeHalfM2 / 2 - 100);
    ArduinoCloud.update();
    delay(CupSizeHalfM2 / 2 - 100);
    
    carrier.Relay1.close();
    delay(1000);
    ReadyScreen();
    AllLeds(0, 255, 0);
    AllPixels(0, 255, 0);
    carrier.Buzzer.sound(1000);
    delay(200);
    carrier.Buzzer.noSound();
    delay(100);
    carrier.Buzzer.sound(1500);
    delay(200);
    carrier.Buzzer.noSound();
    v++;
    MainScreen();
    if (lights == 0) {
      AllLeds(0, 0, 0);
      AllPixels(0, 0, 0);
    }
    else {
      if (lightColor == 1){
        AllLeds(255, 0, 0);
        AllPixels(255, 0, 0);
      }
      if (lightColor == 2){
        AllLeds(255, 255, 0);
        AllPixels(255, 255, 0);
      }
      if (lightColor == 3){
        AllLeds(0, 255, 0);
        AllPixels(0, 255, 0);
      }
      if (lightColor == 4){
        AllLeds(0, 251, 255);
        AllPixels(0, 251, 255);
      }
      if (lightColor == 5){
        AllLeds(0, 0, 255);
        AllPixels(0, 0, 255);
      }
    }
    counter++;
  } 
}

void onDrink1FullChange()  {
  if (drink1Full == true){
    Serial.print(" Drink 1F : true ");
    carrier.Buzzer.sound(4000);
    delay(200);
    carrier.Buzzer.noSound();
    MakingScreen();
    AllLeds(255, 255, 0);
    AllPixels(255, 255, 0);
    carrier.Relay2.open();
    
    delay(CupSizeFullM1 / 2 - 100);
    ArduinoCloud.update();
    delay(CupSizeFullM1 / 2 - 100);
    
    carrier.Relay2.close();
    delay(1000);
    ReadyScreen();
    AllLeds(0, 255, 0);
    AllPixels(0, 255, 0);
    carrier.Buzzer.sound(1000);
    delay(200);
    carrier.Buzzer.noSound();
    delay(100);
    carrier.Buzzer.sound(1500);
    delay(200);
    carrier.Buzzer.noSound();
    v++;
    MainScreen();
    if (lights == 0) {
      AllLeds(0, 0, 0);
      AllPixels(0, 0, 0);
    }
    else {
      if (lightColor == 1){
        AllLeds(255, 0, 0);
        AllPixels(255, 0, 0);
      }
      if (lightColor == 2){
        AllLeds(255, 255, 0);
        AllPixels(255, 255, 0);
      }
      if (lightColor == 3){
        AllLeds(0, 255, 0);
        AllPixels(0, 255, 0);
      }
      if (lightColor == 4){
        AllLeds(0, 251, 255);
        AllPixels(0, 251, 255);
      }
      if (lightColor == 5){
        AllLeds(0, 0, 255);
        AllPixels(0, 0, 255);
      }
    }
    counter++;
  }
}

void onDrink2FullChange()  {
  if (drink2Full == true){
    Serial.print(" Drink 2F : true ");
    carrier.Buzzer.sound(4000);
    delay(200);
    carrier.Buzzer.noSound();
    MakingScreen();
    AllLeds(255, 255, 0);
    AllPixels(255, 255, 0);
    carrier.Relay1.open();
    
    delay(CupSizeFullM2 / 2 - 100);
    ArduinoCloud.update();
    delay(CupSizeFullM2 / 2 - 100);
    
    carrier.Relay1.close();
    delay(1000);
    ReadyScreen();
    AllLeds(0, 255, 0);
    AllPixels(0, 255, 0);
    carrier.Buzzer.sound(1000);
    delay(200);
    carrier.Buzzer.noSound();
    delay(100);
    carrier.Buzzer.sound(1500);
    delay(200);
    carrier.Buzzer.noSound();
    v++;
    MainScreen();
    if (lights == 0) {
      AllLeds(0, 0, 0);
      AllPixels(0, 0, 0);
    }
    else {
      if (lightColor == 1){
        AllLeds(255, 0, 0);
        AllPixels(255, 0, 0);
      }
      if (lightColor == 2){
        AllLeds(255, 255, 0);
        AllPixels(255, 255, 0);
      }
      if (lightColor == 3){
        AllLeds(0, 255, 0);
        AllPixels(0, 255, 0);
      }
      if (lightColor == 4){
        AllLeds(0, 251, 255);
        AllPixels(0, 251, 255);
      }
      if (lightColor == 5){
        AllLeds(0, 0, 255);
        AllPixels(0, 0, 255);
      }
    }
    counter++;
  }
}

void onLightsChange()  {
  if(lights == true){
    carrier.Buzzer.sound(4000);
    delay(200);
    carrier.Buzzer.noSound();
    Serial.print(" Lights : ON ");
    if (lightColor == 1){
    carrier.display.fillScreen(Red);
    }
    if (lightColor == 2){
      carrier.display.fillScreen(Yellow);
    }
    if (lightColor == 3){
      carrier.display.fillScreen(Green);
    }
    if (lightColor == 4){
      carrier.display.fillScreen(Cyan);
    }
    if (lightColor == 5){
      carrier.display.fillScreen(Blue);
    }
    carrier.display.setTextColor(Black);
    carrier.display.setTextSize(3);
    carrier.display.setCursor(65, 70);
    carrier.display.print("Lights");
    carrier.display.setCursor(104, 130);
    carrier.display.print("ON");
    if (lightColor == 1){
      AllLeds(255, 0, 0);
      AllPixels(255, 0, 0);
    }
    if (lightColor == 2){
      AllLeds(255, 255, 0);
      AllPixels(255, 255, 0);
    }
    if (lightColor == 3){
      AllLeds(0, 255, 0);
      AllPixels(0, 255, 0);
    }
    if (lightColor == 4){
      AllLeds(0, 251, 255);
      AllPixels(0, 251, 255);
    }
    if (lightColor == 5){
      AllLeds(0, 0, 255);
      AllPixels(0, 0, 255);
    }
    MainScreen();
    lights = 1;
  }
  else{
    carrier.Buzzer.sound(4000);
    delay(200);
    carrier.Buzzer.noSound();
    Serial.print(" Lights : OFF ");
    if (lightColor == 1){
    carrier.display.fillScreen(Red);
    }
    if (lightColor == 2){
      carrier.display.fillScreen(Yellow);
    }
    if (lightColor == 3){
      carrier.display.fillScreen(Green);
    }
    if (lightColor == 4){
      carrier.display.fillScreen(Cyan);
    }
    if (lightColor == 5){
      carrier.display.fillScreen(Blue);
    }
    carrier.display.setTextColor(Black);
    carrier.display.setTextSize(3);
    carrier.display.setCursor(65, 70);
    carrier.display.print("Lights");
    carrier.display.setCursor(100, 130);
    carrier.display.print("OFF");
    AllLeds(0, 0, 0);
    AllPixels(0, 0, 0);
    MainScreen();
    lights = 0;
  }
}

void MainScreen()  {
  if (lightColor == 1){
    carrier.display.fillScreen(Red);
  }
  if (lightColor == 2){
    carrier.display.fillScreen(Yellow);
  }
  if (lightColor == 3){
    carrier.display.fillScreen(Green);
  }
  if (lightColor == 4){
    carrier.display.fillScreen(Cyan);
  }
  if (lightColor == 5){
    carrier.display.fillScreen(Blue);
  }
  //carrier.display.fillScreen(Cyan);
  carrier.display.setTextColor(Black);
  carrier.display.setTextSize(HomeScreenTextSize);
  
  carrier.display.setCursor(82, 20);
  carrier.display.print("Lights");
  carrier.display.setCursor(79, 50);
  carrier.display.print("on/off");
  
  carrier.display.setCursor(Drink1Coordinates_X, Drink1Coordinates_Y);
  carrier.display.print(Drink1);
  
  carrier.display.setCursor(Drink2Coordinates_X, Drink2Coordinates_Y);
  carrier.display.print(Drink2);
  
}

void AllPixels(int r, int g, int b)  {
  int p = 0;
  while (p <= 17){
    strip.setPixelColor(p, r, g, b);
    strip.show();
    delay(100);
    p++;
  }
}
  
void AllLeds(int r, int g, int b)  {
  int l = 0;
  while (l <= 5){
    carrier.leds.setBrightness(30);
    carrier.leds.setPixelColor(l, g, r, b);
    carrier.leds.show();
    delay(100);
    l++;
  }
  
}

void CheckBt2(){
  carrier.Buttons.update();
  if (carrier.Buttons.onTouchDown(TOUCH2)) {
    carrier.Buzzer.sound(4000);
    delay(200);
    carrier.Buzzer.noSound();
    if (lights == 0) {
      if (lightColor == 1){
        carrier.display.fillScreen(Red);
      }
      if (lightColor == 2){
        carrier.display.fillScreen(Yellow);
      }
      if (lightColor == 3){
        carrier.display.fillScreen(Green);
      }
      if (lightColor == 4){
        carrier.display.fillScreen(Cyan);
      }
      if (lightColor == 5){
        carrier.display.fillScreen(Blue);
      }
      carrier.display.setTextColor(Black);
      carrier.display.setTextSize(3);
      carrier.display.setCursor(65, 70);
      carrier.display.print("Lights");
      carrier.display.setCursor(104, 130);
      carrier.display.print("ON");
      
      if (lightColor == 1){
        AllLeds(255, 0, 0);
        AllPixels(255, 0, 0);
      }
      if (lightColor == 2){
        AllLeds(255, 255, 0);
        AllPixels(255, 255, 0);
      }
      if (lightColor == 3){
        AllLeds(0, 255, 0);
        AllPixels(0, 255, 0);
      }
      if (lightColor == 4){
        AllLeds(0, 251, 255);
        AllPixels(0, 251, 255);
      }
      if (lightColor == 5){
        AllLeds(0, 0, 255);
        AllPixels(0, 0, 255);
      }
      lights = 1;
      
      MainScreen();
    }
    else {
      if (lightColor == 1){
        carrier.display.fillScreen(Red);
      }
      if (lightColor == 2){
        carrier.display.fillScreen(Yellow);
      }
      if (lightColor == 3){
        carrier.display.fillScreen(Green);
      }
      if (lightColor == 4){
        carrier.display.fillScreen(Cyan);
      }
      if (lightColor == 5){
        carrier.display.fillScreen(Blue);
      }
      carrier.display.setTextColor(Black);
      carrier.display.setTextSize(3);
      carrier.display.setCursor(65, 70);
      carrier.display.print("Lights");
      carrier.display.setCursor(100, 130);
      carrier.display.print("OFF");
      
      AllLeds(0, 0, 0);
      AllPixels(0, 0, 0);
      lights = 0;
      
      MainScreen();
    }
  }
}

void CheckBt4(){
  carrier.Buttons.update();
  if (carrier.Buttons.onTouchDown(TOUCH4)) {
    SizeScreen();
    carrier.Buzzer.sound(4000);
    delay(200);
    carrier.Buzzer.noSound();
    v = 0;
    while (v == 0){
      carrier.Buttons.update();
      if (carrier.Buttons.onTouchDown(TOUCH1)) { // Half
        carrier.Buzzer.sound(4000);
        delay(200);
        carrier.Buzzer.noSound();
        MakingScreen();
        AllLeds(255, 255, 0);
        AllPixels(255, 255, 0);
        carrier.Relay1.open();
        
        delay(CupSizeHalfM2 / 2 - 100);
        ArduinoCloud.update();
        delay(CupSizeHalfM2 / 2 - 100);
        
        carrier.Relay1.close();
        delay(1000);
        ReadyScreen();
        AllLeds(0, 255, 0);
        AllPixels(0, 255, 0);
        carrier.Buzzer.sound(1000);
        delay(200);
        carrier.Buzzer.noSound();
        delay(100);
        carrier.Buzzer.sound(1500);
        delay(200);
        carrier.Buzzer.noSound();
        v++;
        MainScreen();
        if (lights == 0) {
          AllLeds(0, 0, 0);
          AllPixels(0, 0, 0);
        }
        else {
          if (lightColor == 1){
            AllLeds(255, 0, 0);
            AllPixels(255, 0, 0);
          }
          if (lightColor == 2){
            AllLeds(255, 255, 0);
            AllPixels(255, 255, 0);
          }
          if (lightColor == 3){
            AllLeds(0, 255, 0);
            AllPixels(0, 255, 0);
          }
          if (lightColor == 4){
            AllLeds(0, 251, 255);
            AllPixels(0, 251, 255);
          }
          if (lightColor == 5){
            AllLeds(0, 0, 255);
            AllPixels(0, 0, 255);
          }
        }
        counter++;
      }
      if (carrier.Buttons.onTouchDown(TOUCH3)) { // Full
        carrier.Buzzer.sound(4000);
        delay(200);
        carrier.Buzzer.noSound();
        MakingScreen();
        AllLeds(255, 255, 0);
        AllPixels(255, 255, 0);
        carrier.Relay1.open();
       
        delay(CupSizeFullM2 / 2 - 100);
        ArduinoCloud.update();
        delay(CupSizeFullM2 / 2 - 100);
        
        carrier.Relay1.close();
        delay(1000);
        ReadyScreen();
        AllLeds(0, 255, 0);
        AllPixels(0, 255, 0);
        carrier.Buzzer.sound(1000);
        delay(200);
        carrier.Buzzer.noSound();
        delay(100);
        carrier.Buzzer.sound(1500);
        delay(200);
        carrier.Buzzer.noSound();
        v++;
        MainScreen();
        if (lights == 0) {
          AllLeds(0, 0, 0);
          AllPixels(0, 0, 0);
        }
        else {
          if (lightColor == 1){
            AllLeds(255, 0, 0);
            AllPixels(255, 0, 0);
          }
          if (lightColor == 2){
            AllLeds(255, 255, 0);
            AllPixels(255, 255, 0);
          }
          if (lightColor == 3){
            AllLeds(0, 255, 0);
            AllPixels(0, 255, 0);
          }
          if (lightColor == 4){
            AllLeds(0, 251, 255);
            AllPixels(0, 251, 255);
          }
          if (lightColor == 5){
            AllLeds(0, 0, 255);
            AllPixels(0, 0, 255);
          }
        }
        counter++;
      }
    }
  }
}

void CheckBt0(){
  carrier.Buttons.update();
  if (carrier.Buttons.onTouchDown(TOUCH0)) {
    SizeScreen();
    carrier.Buzzer.sound(4000);
    delay(200);
    carrier.Buzzer.noSound();
    v = 0;
    while (v == 0){
      carrier.Buttons.update();
      if (carrier.Buttons.onTouchDown(TOUCH1)) { // Half
        carrier.Buzzer.sound(4000);
        delay(200);
        carrier.Buzzer.noSound();
        MakingScreen();
        AllLeds(255, 255, 0);
        AllPixels(255, 255, 0);
        carrier.Relay2.open();
  
        delay(CupSizeHalfM1 / 2 - 100);
        ArduinoCloud.update();
        delay(CupSizeHalfM1 / 2 - 100);

        carrier.Relay2.close();
        delay(1000);
        ReadyScreen();
        AllLeds(0, 255, 0);
        AllPixels(0, 255, 0);
        carrier.Buzzer.sound(1000);
        delay(200);
        carrier.Buzzer.noSound();
        delay(100);
        carrier.Buzzer.sound(1500);
        delay(200);
        carrier.Buzzer.noSound();
        v++;
        MainScreen();
        if (lights == 0) {
          AllLeds(0, 0, 0);
          AllPixels(0, 0, 0);
        }
        else {
          if (lightColor == 1){
            AllLeds(255, 0, 0);
            AllPixels(255, 0, 0);
          }
          if (lightColor == 2){
            AllLeds(255, 255, 0);
            AllPixels(255, 255, 0);
          }
          if (lightColor == 3){
            AllLeds(0, 255, 0);
            AllPixels(0, 255, 0);
          }
          if (lightColor == 4){
            AllLeds(0, 251, 255);
            AllPixels(0, 251, 255);
          }
          if (lightColor == 5){
            AllLeds(0, 0, 255);
            AllPixels(0, 0, 255);
          }
        }
        counter++;
      }
      if (carrier.Buttons.onTouchDown(TOUCH3)) { // Full
        carrier.Buzzer.sound(4000);
        delay(200);
        carrier.Buzzer.noSound();
        MakingScreen();
        AllLeds(255, 255, 0);
        AllPixels(255, 255, 0);
        carrier.Relay2.open();
        
        delay(CupSizeFullM1 / 2 - 100);
        ArduinoCloud.update();
        delay(CupSizeFullM1 / 2 - 100);
        
        carrier.Relay2.close();
        delay(1000);
        ReadyScreen();
        AllLeds(0, 255, 0);
        AllPixels(0, 255, 0);
        carrier.Buzzer.sound(1000);
        delay(200);
        carrier.Buzzer.noSound();
        delay(100);
        carrier.Buzzer.sound(1500);
        delay(200);
        carrier.Buzzer.noSound();
        v++;
        MainScreen();
        if (lights == 0) {
          AllLeds(0, 0, 0);
          AllPixels(0, 0, 0);
        }
        else {
          if (lightColor == 1){
            AllLeds(255, 0, 0);
            AllPixels(255, 0, 0);
          }
          if (lightColor == 2){
            AllLeds(255, 255, 0);
            AllPixels(255, 255, 0);
          }
          if (lightColor == 3){
            AllLeds(0, 255, 0);
            AllPixels(0, 255, 0);
          }
          if (lightColor == 4){
            AllLeds(0, 251, 255);
            AllPixels(0, 251, 255);
          }
          if (lightColor == 5){
            AllLeds(0, 0, 255);
            AllPixels(0, 0, 255);
          }
        }
        counter++;
      }
    }
  }
}

void SizeScreen()  {
  if (lightColor == 1){
    carrier.display.fillScreen(Red);
  }
  if (lightColor == 2){
    carrier.display.fillScreen(Yellow);
  }
  if (lightColor == 3){
    carrier.display.fillScreen(Green);
  }
  if (lightColor == 4){
    carrier.display.fillScreen(Cyan);
  }
  if (lightColor == 5){
    carrier.display.fillScreen(Blue);
  }
  carrier.display.setTextColor(Black);
  carrier.display.setTextSize(3);
  carrier.display.setCursor(82, 180);
  carrier.display.print("Size");
  carrier.display.setCursor(28, 75);
  carrier.leds.setPixelColor(1, 100, 100, 100);
  carrier.leds.setPixelColor(3, 100, 100, 100);
  carrier.leds.show();
  carrier.display.print("HALF");
  carrier.display.setCursor(150, 75);
  carrier.display.print("FULL");
  
}

void MakingScreen() {
  carrier.display.fillScreen(Yellow);
  carrier.display.setTextColor(Black);
  carrier.display.setTextSize(3);
  carrier.display.setCursor(24, 70);
  carrier.display.print("Making your");
  carrier.display.setCursor(45, 140);
  carrier.display.print("drink...");
  
}

void ReadyScreen(){
  carrier.display.fillScreen(Green);
  carrier.display.setTextColor(Black);
  carrier.display.setTextSize(3);
  carrier.display.setCursor(32, 70);
  carrier.display.print("Your drink");
  carrier.display.setCursor(42, 140);
  carrier.display.print("is ready!");
  
}

void onUsageChange() {
  
}

void onCounterChange()  {
  
}

void onDrink1AlexaChange()  {
  if (drink1_Alexa == true){
    Serial.print(" Drink1_Alexa : true ");
    carrier.Buzzer.sound(4000);
    delay(200);
    carrier.Buzzer.noSound();
    MakingScreen();
    AllLeds(255, 255, 0);
    AllPixels(255, 255, 0);
    carrier.Relay2.open();
    
    delay(CupSizeFullM1 / 2 - 100);
    ArduinoCloud.update();
    delay(CupSizeFullM1 / 2 - 100);
    
    carrier.Relay2.close();
    delay(1000);
    ReadyScreen();
    AllLeds(0, 255, 0);
    AllPixels(0, 255, 0);
    carrier.Buzzer.sound(1000);
    delay(200);
    carrier.Buzzer.noSound();
    delay(100);
    carrier.Buzzer.sound(1500);
    delay(200);
    carrier.Buzzer.noSound();
    v++;
    MainScreen();
    if (lights == 0) {
      AllLeds(0, 0, 0);
      AllPixels(0, 0, 0);
    }
    else {
      if (lightColor == 1){
        AllLeds(255, 0, 0);
        AllPixels(255, 0, 0);
      }
      if (lightColor == 2){
        AllLeds(255, 255, 0);
        AllPixels(255, 255, 0);
      }
      if (lightColor == 3){
        AllLeds(0, 255, 0);
        AllPixels(0, 255, 0);
      }
      if (lightColor == 4){
        AllLeds(0, 251, 255);
        AllPixels(0, 251, 255);
      }
      if (lightColor == 5){
        AllLeds(0, 0, 255);
        AllPixels(0, 0, 255);
      }
    }
    counter++;
  }
}

void onDrink2AlexaChange()  {
  if (drink2_Alexa == true){
    Serial.print(" Drink2_Alexa : true ");
    carrier.Buzzer.sound(4000);
    delay(200);
    carrier.Buzzer.noSound();
    MakingScreen();
    AllLeds(255, 255, 0);
    AllPixels(255, 255, 0);
    carrier.Relay1.open();
    
    delay(CupSizeFullM2 / 2 - 100);
    ArduinoCloud.update();
    delay(CupSizeFullM2 / 2 - 100);
    
    carrier.Relay1.close();
    delay(1000);
    ReadyScreen();
    AllLeds(0, 255, 0);
    AllPixels(0, 255, 0);
    carrier.Buzzer.sound(1000);
    delay(200);
    carrier.Buzzer.noSound();
    delay(100);
    carrier.Buzzer.sound(1500);
    delay(200);
    carrier.Buzzer.noSound();
    v++;
    MainScreen();
    if (lights == 0) {
      AllLeds(0, 0, 0);
      AllPixels(0, 0, 0);
    }
    else {
      if (lightColor == 1){
        AllLeds(255, 0, 0);
        AllPixels(255, 0, 0);
      }
      if (lightColor == 2){
        AllLeds(255, 255, 0);
        AllPixels(255, 255, 0);
      }
      if (lightColor == 3){
        AllLeds(0, 255, 0);
        AllPixels(0, 255, 0);
      }
      if (lightColor == 4){
        AllLeds(0, 251, 255);
        AllPixels(0, 251, 255);
      }
      if (lightColor == 5){
        AllLeds(0, 0, 255);
        AllPixels(0, 0, 255);
      }
    }
    counter++;
  }
}
