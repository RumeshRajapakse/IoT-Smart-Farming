#include <LiquidCrystal.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
LiquidCrystal_I2C lcd(0x27,20,4);
#define ENVTEMP A0  // read the environmental temperature and humidity
#define WATTEMP A1  // read the water temperature
#define DHT1TYPE DHT11   // DHT 11 
#define DHT2TYPE DHT11   // DHT 11 

DHT dht1(ENVTEMP, DHT1TYPE);
DHT dht2(WATTEMP, DHT2TYPE);

void setup() {
Serial.begin(9600);
  lcd.init();  
  lcd.backlight();
  lcd.init();
  dht1.begin();
  dht2.begin();
}
 
void loop() {
  //reading temperature and humidity from sensor
 float h1 = dht1.readHumidity();
 float t1 = dht1.readTemperature();
 float h2 = dht2.readHumidity();
 float t2 = dht2.readTemperature();
 
 
  //printing the sensor values through serial printer
 
 Serial.print("tout=");
 Serial.println(t1);
 Serial.print("hout=");
 Serial.println(h1);
 Serial.print("tin=");
 Serial.println(t2);
 Serial.print("hin=");
 Serial.println(h2);

 delay(2500); // delay between reading each sensor data
}
