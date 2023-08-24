#include <Arduino.h>

#define motor1A 5
#define motor1B 6
#define motor1_EN 7  //一定要接且給予電壓(0~255)
#define motor2A 8
#define motor2B 10
#define motor2_EN 11

int timecount = 0;
int left_red_value = 0;
int right_red_value = 0;

void setup() {
  Serial.begin(9600);
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor1_EN, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(motor2_EN, OUTPUT);

  pinMode(A0, INPUT);  //左側紅外線感測器
  pinMode(A1, INPUT);  //右側紅外線感測器
}

void backward() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
  analogWrite(motor1_EN, 130);
  analogWrite(motor2_EN, 150);
  Serial.println("b");
  delay(150);
}

void forward() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  analogWrite(motor1_EN, 128);
  analogWrite(motor2_EN, 255);  
  Serial.println("f");
  delay(70);
}

void right() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
  analogWrite(motor1_EN, 130);
  analogWrite(motor2_EN, 130); 
  Serial.println("r");   
  delay(60); 
}

void left() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  analogWrite(motor1_EN, 130);
  analogWrite(motor2_EN, 130);
  Serial.println("l");
  delay(60);
}

void stop() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
  analogWrite(motor1_EN, 0);
  analogWrite(motor2_EN, 0);
  Serial.println("s");       
  delay(100);
}

void loop() {
  //紅外線感測器
  right_red_value = analogRead(A0);
  left_red_value = analogRead(A1);
  if(left_red_value < 800 && right_red_value > 800)
  {
    right();
  }
  else if (left_red_value > 800 && right_red_value < 800)
  {
    left();
  }
  else if (left_red_value < 800 && right_red_value < 800)
  {
    forward();
    //left a little
    digitalWrite(motor1A, LOW);
    digitalWrite(motor1B, HIGH);
    digitalWrite(motor2A, HIGH);
    digitalWrite(motor2B, LOW);
    analogWrite(motor1_EN, 130);
    analogWrite(motor2_EN, 130);
    delay(10);
  }
  else
  {
    backward();
  }

  stop();
  delay(50);
  /* Serial.print(left_red_value);
  Serial.print("\t");
  Serial.println(right_red_value); */
}
