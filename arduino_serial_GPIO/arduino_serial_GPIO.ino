int up = 13;
int right = 12;
int down = 11;
int left = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(up, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(down, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(7, OUTPUT);
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

      break;

      case 'c':
//        Serial.println("Go right!");
        digitalWrite(up, LOW);
        digitalWrite(right, HIGH);
        digitalWrite(down, LOW);
        digitalWrite(left, LOW);
      break;
      
      case 'd':
//        Serial.println("Go down!");
        digitalWrite(up, LOW);
        digitalWrite(right, LOW);
        digitalWrite(down, HIGH);
        digitalWrite(left, LOW);
      break;
      
      case 'e':
//        Serial.println("Go left!");
        digitalWrite(up, LOW);
        digitalWrite(right, LOW);
        digitalWrite(down, LOW);
        digitalWrite(left, HIGH);
      break;

      case 'f':
//        Serial.println("Go left!");
        digitalWrite(up, HIGH);
        digitalWrite(right, HIGH);
        digitalWrite(down, LOW);
        digitalWrite(left, LOW);
      break;

      case 'g':
//        Serial.println("Go left!");
        digitalWrite(up, HIGH);
        digitalWrite(right, LOW);
        digitalWrite(down, LOW);
        digitalWrite(left, HIGH);
      break;

      case 'h':
//        Serial.println("Go left!");
        digitalWrite(up, LOW);
        digitalWrite(right, HIGH);
        digitalWrite(down, HIGH);
        digitalWrite(left, LOW);
      break;

        case 'i':
//        Serial.println("Go left!");
        digitalWrite(up, LOW);
        digitalWrite(right, LOW);
        digitalWrite(down, HIGH);
        digitalWrite(left, HIGH);
      break;
    }
  }
}
