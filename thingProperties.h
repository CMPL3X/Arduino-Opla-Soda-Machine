// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char SSID[]     = SECRET_SSID;    // Network SSID (name)
const char PASS[]     = SECRET_PASS;    // Network password (use for WPA, or use as key for WEP)

void onDrink1AlexaChange();
void onDrink2AlexaChange();
void onCounterChange();
void onColorChangeChange();
void onDrink1FullChange();
void onDrink1HalfChange();
void onDrink2FullChange();
void onDrink2HalfChange();
void onLightsChange();
void onPumpTestChange();

CloudSwitch drink1_Alexa;
CloudSwitch drink2_Alexa;
int counter;
bool colorChange;
bool drink1Full;
bool drink1Half;
bool drink2Full;
bool drink2Half;
bool lights;
bool pumpTest;

void initProperties(){

  ArduinoCloud.addProperty(drink1_Alexa, READWRITE, ON_CHANGE, onDrink1AlexaChange);
  ArduinoCloud.addProperty(drink2_Alexa, READWRITE, ON_CHANGE, onDrink2AlexaChange);
  ArduinoCloud.addProperty(counter, READWRITE, ON_CHANGE, onCounterChange, 1);
  ArduinoCloud.addProperty(colorChange, READWRITE, ON_CHANGE, onColorChangeChange);
  ArduinoCloud.addProperty(drink1Full, READWRITE, ON_CHANGE, onDrink1FullChange);
  ArduinoCloud.addProperty(drink1Half, READWRITE, ON_CHANGE, onDrink1HalfChange);
  ArduinoCloud.addProperty(drink2Full, READWRITE, ON_CHANGE, onDrink2FullChange);
  ArduinoCloud.addProperty(drink2Half, READWRITE, ON_CHANGE, onDrink2HalfChange);
  ArduinoCloud.addProperty(lights, READWRITE, ON_CHANGE, onLightsChange);
  ArduinoCloud.addProperty(pumpTest, READWRITE, ON_CHANGE, onPumpTestChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
