#include <Servo.h>

// Assign LED pins to variables
int up = 13;
int right = 12;
int down = 11;
int left = 10;

// Assign servo pins to variables
int horizontalServo = 5;
int verticalServo = 6;

// Maximum range of motion for servos
int servoMax = 120;
int servoMin = 20;

// Maximum adjustment possible per tick
int curHServoAngle = 70;
int curVServoAngle = 70;
int servoAdjustmentRate = 1;

// Set up servo variables
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
          digitalWrite(up, LOW);
          digitalWrite(right, LOW);
          digitalWrite(down, LOW);
          digitalWrite(left, LOW);
      break;

      case 'b':
        digitalWrite(up, HIGH);
        digitalWrite(right, LOW);
        digitalWrite(down, LOW);
        digitalWrite(left, LOW);

        vServoUp();
      break;

      case 'c':
        digitalWrite(up, LOW);
        digitalWrite(right, HIGH);
        digitalWrite(down, LOW);
        digitalWrite(left, LOW);

        hServoUp();
      break;
      
      case 'd':
        digitalWrite(up, LOW);
        digitalWrite(right, LOW);
        digitalWrite(down, HIGH);
        digitalWrite(left, LOW);

        vServoDown();
      break;
      
      case 'e':
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
  delay(25);
}
