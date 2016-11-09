#include <SoftwareSerial.h>

#define Rx 0
#define Tx 1

#define MOTOR12B 2
#define MOTOR1PWM 3
#define MOTOR2PWM 5
#define MOTOR12A 7

#define MOTOR34B 8
#define MOTOR3PWM 9
#define MOTOR4PWM 11
#define MOTOR34A 13

#define trigPinRightSensor A0
#define echoPinRightSensor A1
#define trigPinMidSensor A2
#define echoPinMidSensor A3
#define trigPinLeftSensor A4
#define echoPinLeftSensor A5

long distanceMidSensor;
long durationMidSensor;
long distanceRightSensor;
long durationRightSensor;
long distanceLeftSensor;
long durationLeftSensor;

int x = 0;

SoftwareSerial blueToothShield (Rx,Tx);

void setup() {
  //Motor pins
  pinMode(MOTOR12B,OUTPUT);
  pinMode(MOTOR12A,OUTPUT);
  
  pinMode(MOTOR34B,OUTPUT);
  pinMode(MOTOR34A,OUTPUT);
  
  //Ultrasound sensor pins
  pinMode(trigPinMidSensor, OUTPUT);
  pinMode(echoPinMidSensor, INPUT);
  pinMode(trigPinRightSensor, OUTPUT);
  pinMode(echoPinRightSensor, INPUT);
  pinMode(trigPinLeftSensor, OUTPUT);
  pinMode(echoPinLeftSensor, INPUT);
  
  //Initializing bluetooth communication
  blueToothShield.begin(9600);
  blueToothShield.println ("1 - Forward");
  blueToothShield.println ("2 - Right");
  blueToothShield.println ("3 - Left");
  blueToothShield.println ("4 - Backward");
  blueToothShield.println ("5 - Automatic");
  blueToothShield.println ("6 - Stop, Press and Hold");
}

//detect distance using ultrasonic sensors
void detect() {
  
  //Mid Sensor
  digitalWrite(trigPinMidSensor, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPinMidSensor, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPinMidSensor, LOW);
  
  durationMidSensor = pulseIn(echoPinMidSensor, HIGH);
  distanceMidSensor = (durationMidSensor/2) / 29.1; //convert to cm
  blueToothShield.print("Mid: ");
  blueToothShield.print(distanceMidSensor);
  blueToothShield.println ("cm");

  //Right Sensor  
  digitalWrite(trigPinRightSensor, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPinRightSensor, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPinRightSensor, LOW);
  
  durationRightSensor = pulseIn(echoPinRightSensor, HIGH);
  distanceRightSensor = (durationRightSensor/2) / 29.1; //convert to cm
  blueToothShield.print("Right: ");
  blueToothShield.print(distanceRightSensor);
  blueToothShield.println ("cm");

  //Left sensor
  digitalWrite(trigPinLeftSensor, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPinLeftSensor, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPinLeftSensor, LOW);
  
  durationLeftSensor = pulseIn(echoPinLeftSensor, HIGH);
  distanceLeftSensor = (durationLeftSensor/2) / 29.1; //convert to cm
  blueToothShield.print("Left: ");
  blueToothShield.print(distanceLeftSensor);
  blueToothShield.println ("cm");
  blueToothShield.println ("");

}

void stop() {
    digitalWrite(MOTOR12B,LOW);
    digitalWrite(MOTOR12A,LOW);
    digitalWrite(MOTOR34B,LOW);
    digitalWrite(MOTOR34A,LOW);
}

void forward() {
    digitalWrite(MOTOR12A,LOW);
    digitalWrite(MOTOR12B,HIGH);
    analogWrite(MOTOR1PWM,255);
    analogWrite(MOTOR2PWM,255);

    digitalWrite(MOTOR34A,LOW);
    digitalWrite(MOTOR34B,HIGH);
    analogWrite(MOTOR3PWM,215);
    analogWrite(MOTOR4PWM,215);
}

void backward() {
    digitalWrite(MOTOR12A,HIGH);
    digitalWrite(MOTOR12B,LOW);
    analogWrite(MOTOR1PWM,255);
    analogWrite(MOTOR2PWM,255);

    digitalWrite(MOTOR34A,HIGH);
    digitalWrite(MOTOR34B,LOW);
    analogWrite(MOTOR3PWM,215);
    analogWrite(MOTOR4PWM,215);
}


void right() {
    digitalWrite(MOTOR12A,LOW);
    digitalWrite(MOTOR12B,HIGH);
    analogWrite(MOTOR1PWM,255);
    analogWrite(MOTOR2PWM,255);

    digitalWrite(MOTOR34A,HIGH);
    digitalWrite(MOTOR34B,LOW);
    analogWrite(MOTOR3PWM,255);
    analogWrite(MOTOR4PWM,255);
}

void left() {
    digitalWrite(MOTOR12A,HIGH);
    digitalWrite(MOTOR12B,LOW);
    analogWrite(MOTOR1PWM,255);
    analogWrite(MOTOR2PWM,255);

    digitalWrite(MOTOR34A,LOW);
    digitalWrite(MOTOR34B,HIGH);
    analogWrite(MOTOR3PWM,255);
    analogWrite(MOTOR4PWM,255);
}

void detect_auto() {
    do {
      detect();
      x = blueToothShield.read();
      if (x == '6') {
        break;
      }
    } while (distanceLeftSensor < 100 && distanceRightSensor < 100);  
}

void automatic () {
  while (blueToothShield.read() != '6') {
    forward();
    detect();
    while ((distanceLeftSensor > 45 || distanceLeftSensor == 0 ) && (distanceRightSensor > 45 || distanceRightSensor == 0) && (distanceMidSensor > 45 || distanceMidSensor == 0)) {
      detect();
      if (blueToothShield.read() == '6') {
        break;
      }
    }
    left();
    delay(1865);
  }
  stop();
}

void loop() {
  char direction; //user selection
    
  if (blueToothShield.available()) {

    direction = blueToothShield.read();
    
    switch (direction) {
    case '1':
      blueToothShield.println("Moving Forward...");
      forward();
      break;
    case '2':
      blueToothShield.println("Turning Right...");
      right();
      break;
    case '3':
      blueToothShield.println("Turning Left...");
      left();
      break;
    case '4':
      blueToothShield.println("Moving Backward...");
      backward();
      break;
    case '5':
      blueToothShield.println("Automatic Cruise");
      automatic();
      break;
    case '6':
      stop();
      break;
    }
  }
}
