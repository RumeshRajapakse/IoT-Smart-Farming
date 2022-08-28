#include <BH1750.h>
#include <Wire.h>
#include "DHT.h"

#define ENVTEMP A0  // DHT11 sensor data pin connected to

#define co2sensor A1 // co2 sensor data pin connected to

#define watertemp A2 // water temp data pin connected to

#define ph A3 // pH sensor data pin connected to

BH1750 lightMeter(0x23); // address of the light sensor. SDL and SCL pins are connected to A4 and A5

// configure co2 sensor
int gas, co2lvl;

// configure the ph sensor
float calibration_value = 21.34 - 0.45;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;

float ph_act;

// configure DHT
#define DHT1TYPE DHT11   // DHT 11 

DHT dht1(ENVTEMP, DHT1TYPE);

void setup() {
Wire.begin();
Serial.begin(9600);
dht1.begin();

//co2 sensor setup
pinMode(co2sensor, INPUT);

  //error handling and reading light sensor
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println(F("BH1750 Advanced begin"));
  } else {
    Serial.println(F("Error initialising BH1750"));
  }
}
 
void loop() {

  
  //reading temperature and humidity from sensor
 float temp = dht1.readTemperature(); // temperature reading of the environment
 float humidity = dht1.readHumidity(); // humidity of the environment

 // reading light sensor
 if (lightMeter.measurementReady()) {
    float lux = lightMeter.readLightLevel();
    
 float watertemp = analogRead(watertemp); // temperature reading of water
 float tds = dht1.readTemperature(); // nutrients solved in water
 float wlvl = dht1.readTemperature(); // Water level at the plant roots

 // read ph sensor values
for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(A3);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*5.0/1024/6; 
  ph_act = -5.70 * volt + calibration_value;


// read co2 values

  gas= analogRead(co2sensor);
  co2lvl = gas - 142;
  co2lvl = map(co2lvl,0,1024,400,5000);
 
  //Sensor values are printed through serial port in the json format
 
 Serial.print("{\"temp\":");
 Serial.print(temp);
 Serial.print(",\"humidity\":");
 Serial.print(humidity);
 Serial.print(",\"watertemp\":");
 Serial.print(watertemp);
 Serial.print(",\"ph\":");
 Serial.print(ph_act);
 Serial.print(",\"tds\":");
 Serial.print(tds);
 Serial.print(",\"co2\":");
 Serial.print(co2lvl);
 Serial.print(",\"waterlevel\":");
 Serial.print(wlvl);
 Serial.print(",\"lux\":");
 Serial.print(lux);
 Serial.print("}");
 Serial.println();
 delay(3500); // delay between reading each sensor data
}
}
