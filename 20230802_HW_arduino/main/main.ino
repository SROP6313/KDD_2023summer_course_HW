#include <Arduino.h>
#include <SoftwareSerial.h>

#define motor1A 5
#define motor1B 6
#define motor1_ENA 7  //一定要接且給予電壓(0~255)
#define motor2A 8
#define motor2B 10
#define motor2_ENA 11
#define LED_Pin 13

SoftwareSerial BTserial(2, 3);  // (RX, TX)
String BT_data;                          // to store input character received via BT.
String Arduino_data;
int timecount = 0;

void setup() {
  Serial.begin(9600);
  BTserial.begin(9600);
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor1_ENA, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(motor2_ENA, OUTPUT);
  pinMode(LED_Pin, OUTPUT);
}

void loop() {
  if(BTserial.available())
  {
    BT_data = BTserial.readString();
    //Serial.println(BT_data);
    digitalWrite(LED_Pin, HIGH);
    if (BT_data == "f")
    {
      digitalWrite(motor1A, LOW);
      digitalWrite(motor1B, HIGH);
      digitalWrite(motor2A, LOW);
      digitalWrite(motor2B, HIGH);
      analogWrite(motor1_ENA, 150);
      analogWrite(motor2_ENA, 150);
      timecount = -100; 
      delay(10);
    }
    else if (BT_data == "b")
    {
      digitalWrite(motor1A, HIGH);
      digitalWrite(motor1B, LOW);
      digitalWrite(motor2A, HIGH);
      digitalWrite(motor2B, LOW);
      analogWrite(motor1_ENA, 150);
      analogWrite(motor2_ENA, 150);  
      timecount = -100;    
      delay(10);
    }
    else if (BT_data == "r")
    {
      digitalWrite(motor1A, HIGH);
      digitalWrite(motor1B, LOW);
      digitalWrite(motor2A, LOW);
      digitalWrite(motor2B, HIGH);
      analogWrite(motor1_ENA, 150);
      analogWrite(motor2_ENA, 150); 
      timecount = 0;     
      delay(10);      
    }
    else if (BT_data == "l")
    {
      digitalWrite(motor1A, LOW);
      digitalWrite(motor1B, HIGH);
      digitalWrite(motor2A, HIGH);
      digitalWrite(motor2B, LOW);
      analogWrite(motor1_ENA, 150);
      analogWrite(motor2_ENA, 150);
      timecount = 0;       
      delay(10);
    }
    else
    {
      digitalWrite(motor1A, LOW);
      digitalWrite(motor1B, LOW);
      digitalWrite(motor2A, LOW);
      digitalWrite(motor2B, LOW);
      analogWrite(motor1_ENA, 0);
      analogWrite(motor2_ENA, 0);       
      delay(10);
    }
  }

  Serial.println(BT_data);
  timecount++;
  if(timecount >= 50)
  {
    digitalWrite(motor1A, LOW);
    digitalWrite(motor1B, LOW);
    digitalWrite(motor2A, LOW);
    digitalWrite(motor2B, LOW);
    analogWrite(motor1_ENA, 0);
    analogWrite(motor2_ENA, 0);       
    delay(10);
    timecount = 0;
    digitalWrite(LED_Pin, LOW);
  }
/*   if(Serial.available())
  {
    Arduino_data = Serial.readString();
    BTserial.println(Arduino_data);
  }  */
}