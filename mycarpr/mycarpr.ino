#include <SoftwareSerial.h>
#include<Servo.h>
#include "Ultrasonic.h"
SoftwareSerial mySerial(2, 3); // RX, TX
Ultrasonic ultrasonic(A1 ,A0);//trig pin,echo pin
Servo myservo;


int EN1=7; int EN2=8; int EN3=11; int EN4=12; 
const int pos=90;
bool check=false;
 
void setup() {
  myservo.attach(6); 
  myservo.write(pos);
  delay(3000);
  stopmotor(); 
  Serial.begin(9600);
  mySerial.begin(9600);
  
 pinMode (EN1,OUTPUT); pinMode (EN2,OUTPUT); pinMode (EN3,OUTPUT); pinMode (EN4,OUTPUT);  
  pinMode(A1, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(9, INPUT_PULLUP);
}


void loop() {
 
  if(!digitalRead(9)&&!check){
   delay(50);
   check=true;
  }
  if(check==true){
   sensor();
  }
  else{
    bluetoohsensor();
  }


}
  
