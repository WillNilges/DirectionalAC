int up = 13;
int right = 12;
int down = 11;
int left = 10;
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(up, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(down, OUTPUT);
  pinMode(left, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0){
    int serIn = Serial.read();
    switch(serIn){
      case 'u':
//        Serial.println("Go up!");
        digitalWrite(up, HIGH);
      break;
      case 'd':
//        Serial.println("Go down!");
        digitalWrite(down, HIGH);
      break;
      case 'l':
//        Serial.println("Go left!");
        digitalWrite(left, HIGH);
      break;
      case 'r':
//        Serial.println("Go right!");
        digitalWrite(right, HIGH);
      break;
      case 'h':
//        Serial.println("Horizontal OK");
        digitalWrite(up, LOW);
        digitalWrite(down, LOW);
      break;
      case 'v':
//        Serial.println("Vertical OK");
        digitalWrite(left, LOW);
        digitalWrite(right, LOW);
      break;
      case 'a':
//        Serial.println("Face OK");
        digitalWrite(left, LOW);
        digitalWrite(right, LOW);
        digitalWrite(up, LOW);
        digitalWrite(down, LOW);
    }
//    sleep(1000);
  }
//  else {
    Serial.println("Not getting input!");
//delay(500);
//  }
}
