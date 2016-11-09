#include <SoftwareSerial.h>

#define trigPinMidSensor A2
#define echoPinMidSensor A3
#define trigPinRightSensor A0
#define echoPinRightSensor A1
#define trigPinLeftSensor A4
#define echoPinLeftSensor A5

SoftwareSerial blue (0,1);

void setup() {
  blue.begin (9600);
  pinMode(trigPinMidSensor, OUTPUT);
  pinMode(echoPinMidSensor, INPUT);
  pinMode(trigPinRightSensor, OUTPUT);
  pinMode(echoPinRightSensor, INPUT);
  pinMode(trigPinLeftSensor, OUTPUT);
  pinMode(echoPinLeftSensor, INPUT);
  blue.println("Hello");
}

void loop() {
  if (blue.available()) {
    //Mid Sensor
    long distanceMidSensor;
    long durationMidSensor;
    
    digitalWrite(trigPinMidSensor, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trigPinMidSensor, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trigPinMidSensor, LOW);
    
    durationMidSensor = pulseIn(echoPinMidSensor, HIGH);
    distanceMidSensor = (durationMidSensor/2) / 29.1; //convert to cm
  
    if (distanceMidSensor >= 200 || distanceMidSensor <= 0){
      blue.println("Middle Sensor: Out of range");
    }
    else {
      blue.print("Middle Sensor: ");
      blue.print(distanceMidSensor);
      blue.println(" cm");
    }
  
    //Right Sensor  
    long distanceRightSensor;
    long durationRightSensor;
  
    digitalWrite(trigPinRightSensor, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trigPinRightSensor, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trigPinRightSensor, LOW);
    
    durationRightSensor = pulseIn(echoPinRightSensor, HIGH);
    distanceRightSensor = (durationRightSensor/2) / 29.1; //convert to cm
    
    if (distanceRightSensor >= 200 || distanceRightSensor <= 0){
      blue.println("Right Sensor: Out of range");
    }
    else {
      blue.print("Right Sensor: ");
      blue.print(distanceRightSensor);
      blue.println(" cm");
    }
    
    long distanceLeftSensor;
    long durationLeftSensor;
  
    digitalWrite(trigPinLeftSensor, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trigPinLeftSensor, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trigPinLeftSensor, LOW);
    
    durationLeftSensor = pulseIn(echoPinLeftSensor, HIGH);
    distanceLeftSensor = (durationLeftSensor/2) / 29.1; //convert to cm
    
    if (distanceLeftSensor >= 200 || distanceLeftSensor <= 0){
      blue.println("Left Sensor: Out of range");
    }
    else {
      blue.print("Left Sensor: ");
      blue.print(distanceLeftSensor);
      blue.println(" cm");
    }
    blue.println("");
    
    delay(2000);
  }
}

