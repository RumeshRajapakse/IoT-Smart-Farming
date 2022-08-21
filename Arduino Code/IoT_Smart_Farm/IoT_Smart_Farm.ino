void setup() {
Serial.begin(9600);
}
 
void loop() {
  //Let's generate our random data
 int t = random(20,32);
 int h = random(60,100);
 int rnd = random(1000);
 
  //Note that it won't send it to the pi without the ln in Serial.println
 Serial.print("t=");
 Serial.println(t);
 
 Serial.print("h=");
 Serial.println(h);
 
 Serial.print("random=");
 Serial.println(rnd);
 
 //Wait 2.5 seconds and start the party over again
 delay(2500);
}
