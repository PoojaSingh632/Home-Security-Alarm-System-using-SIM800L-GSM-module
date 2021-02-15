#include <SoftwareSerial.h>
SoftwareSerial sim(10,11);
int sensorvalue2;
 

void setup() {
  // put your setup code here, to run once:
  delay(7000);
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  Serial.println("System Started...");
  
  //Begin serial communication with Arduino and SIM800L
  sim.begin(9600);
  delay(1000);
  pinMode(2, INPUT);

}

void loop() {
  
  readMotion();
  delay(300);
}
void readMotion()
{
 int  sensorValue2 = digitalRead(2);
  if (sensorValue2 == LOW)
  {
     Serial.println("Thief Detected");
     callNumber();
  }
  else
  {
    Serial.println("NOT DETECTED");
  }
}

void callNumber() {
  Serial.println("Initializing..."); 
  delay(1000);

  sim.println("AT"); //Once the handshake test is successful, i t will back to OK
  updateSerial();
  
  sim.println("ATD+ +91XXXXXXXXXX;"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
  updateSerial();
  delay(20000); // wait for 20 seconds...
  sim.println("ATH"); //hang up
  updateSerial();
}
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    sim.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(sim.available()) 
  {
    Serial.write(sim.read());//Forward what Software Serial received to Serial Port
  }
}
