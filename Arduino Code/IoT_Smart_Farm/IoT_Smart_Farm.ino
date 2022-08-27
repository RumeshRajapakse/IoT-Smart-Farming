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
 float temp = dht1.readTemperature(); // temperature reading of the environment
 float humidity = dht1.readHumidity(); // humidity of the environment
 float watertemp = dht2.readTemperature(); // temperature reading od water
 float ph = dht1.readHumidity(); // ph value of the water
 float tds = dht1.readTemperature(); // nutrients solved in water
 float co2 = dht2.readHumidity(); // CO2 concentration of the environment
 float wlvl = dht2.readTemperature(); // Water level at the plant roots
 float lux = dht2.readTemperature(); // light intensity recieved at plants
 
  //Sensor values are printed through serial port in the json format
 
 Serial.print("{\"temp\":");
 Serial.print(temp);
 Serial.print(",\"humidity\":");
 Serial.print(humidity);
 Serial.print(",\"watertemp\":");
 Serial.print(watertemp);
 Serial.print(",\"ph\":");
 Serial.print(ph);
 Serial.print(",\"tds\":");
 Serial.print(tds);
 Serial.print(",\"co2\":");
 Serial.println(co2);
 Serial.print(",\"waterlevel\":");
 Serial.println(wlvl);
 Serial.print(",\"lux\":");
 Serial.println(lux);

 Serial.println("}");
// Serial.print("hin=");
// Serial.println(h2);

 delay(2500); // delay between reading each sensor data
}
