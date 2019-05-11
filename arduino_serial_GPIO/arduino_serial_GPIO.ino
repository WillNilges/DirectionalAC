#include <Servo.h>

int up = 13;
int right = 12;
int down = 11;
int left = 10;

int horizontalServo = 5;
int verticalServo = 6;
int servoMax = 120;
int servoMin = 20;

int curHServoAngle = 70;
int curVServoAngle = 70;
int servoAdjustmentRate = 1;

Servo hServo;
Servo vServo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(up, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(down, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(7, OUTPUT);

  hServo.attach(horizontalServo);
  vServo.attach(verticalServo);
}

void hServoUp(){
  if (curHServoAngle < servoMax){
          curHServoAngle-=servoAdjustmentRate;
          hServo.write(curHServoAngle);
        }
}

void hServoDown(){
  if (curHServoAngle > servoMin){
    curHServoAngle+=servoAdjustmentRate;
    hServo.write(curHServoAngle);
  }
}

void vServoUp(){
  if (curVServoAngle < servoMax){
    curVServoAngle-=servoAdjustmentRate;
    vServo.write(curVServoAngle);
  }
}

void vServoDown(){
  if (curVServoAngle > servoMin){
    curVServoAngle+=servoAdjustmentRate;
    vServo.write(curVServoAngle);
  }
}

void loop() {
  digitalWrite(7, HIGH);
  // put your main code here, to run repeatedly:
  if (Serial.available()>=0){
    int serialIn = Serial.read();

    switch(serialIn){
      case 'a':
//        Serial.println("Face OK");
          digitalWrite(up, LOW);
          digitalWrite(right, LOW);
          digitalWrite(down, LOW);
          digitalWrite(left, LOW);
      break;

      case 'b':
//        Serial.println("Go up!");
        digitalWrite(up, HIGH);
        digitalWrite(right, LOW);
        digitalWrite(down, LOW);
        digitalWrite(left, LOW);

        vServoUp();
      break;

      case 'c':
//        Serial.println("Go right!");
        digitalWrite(up, LOW);
        digitalWrite(right, HIGH);
        digitalWrite(down, LOW);
        digitalWrite(left, LOW);

        hServoUp();
      break;
      
      case 'd':
//        Serial.println("Go down!");
        digitalWrite(up, LOW);
        digitalWrite(right, LOW);
        digitalWrite(down, HIGH);
        digitalWrite(left, LOW);

        vServoDown();
      break;
      
      case 'e':
//        Serial.println("Go left!");
        digitalWrite(up, LOW);
        digitalWrite(right, LOW);
        digitalWrite(down, LOW);
        digitalWrite(left, HIGH);

        hServoDown();
      break;

      case 'f':
        digitalWrite(up, HIGH);
        digitalWrite(right, HIGH);
        digitalWrite(down, LOW);
        digitalWrite(left, LOW);

        hServoUp();
        vServoUp();
      break;

      case 'g':
        digitalWrite(up, HIGH);
        digitalWrite(right, LOW);
        digitalWrite(down, LOW);
        digitalWrite(left, HIGH);
        
        hServoDown();
        vServoUp();
      break;

      case 'h':
        digitalWrite(up, LOW);
        digitalWrite(right, HIGH);
        digitalWrite(down, HIGH);
        digitalWrite(left, LOW);

        hServoUp();
        vServoDown();
      break;

        case 'i':
        digitalWrite(up, LOW);
        digitalWrite(right, LOW);
        digitalWrite(down, HIGH);
        digitalWrite(left, HIGH);

        hServoDown();
        vServoDown();
      break;
    }
  }
  //Serial.print("hServo ");
  //Serial.print(curHServoAngle + "\n");
  //Serial.print("vServo ");
  //Serial.print(curVServoAngle + "\n");
  delay(25);
//  else{
//    hServo.write(50);
//    vServo.write(50);  
//  }
}
