#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x04    // 設定Arduino開發板I2C的位址
int number = 0;
int state = 0;

#define motor1A 5
#define motor1B 6
#define motor1_EN 7  //一定要接且給予電壓(0~255)
#define motor2A 8
#define motor2B 10
#define motor2_EN 11

int timecount = 0;
int left_red_value = 0;
int right_red_value = 0;

void backward() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
  analogWrite(motor1_EN, 130);
  analogWrite(motor2_EN, 150);
  //Serial.println("b");
  delay(150);
}

void forward() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  analogWrite(motor1_EN, 128);
  analogWrite(motor2_EN, 255);  
  //Serial.println("f");
  delay(150);
}

void right() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
  analogWrite(motor1_EN, 150);
  analogWrite(motor2_EN, 150); 
  //Serial.println("r");   
  delay(60); 
}

void left() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  analogWrite(motor1_EN, 150);
  analogWrite(motor2_EN, 150);
  //Serial.println("l");
  delay(60);
}

void stop() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
  analogWrite(motor1_EN, 0);
  analogWrite(motor2_EN, 0);
  //Serial.println("s");       
  delay(100);
}


// callback for received data
void receiveData(int byteCount){
  while(Wire.available())  //當I2C的buffer中有資料時進入迴圈
  {
    number = Wire.read();   //指定nubmer 等於讀取的訊息
    Serial.print("data received: ");
    Serial.println(number);
  }
}

// callback for sending data
void sendData() {
  Wire.write(number);
}

void setup() 
{
  Serial.begin(9600);   // Serial通訊埠通訊設為9600速率
  Wire.begin(SLAVE_ADDRESS);  // 初始化Arduino的I2C位址

  Wire.onReceive(receiveData); //I2C訊號接收時，啟用函式
  //Wire.onRequest(sendData);  //主機要求讀取時，啟用函式
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor1_EN, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(motor2_EN, OUTPUT);

  Serial.println("Ready!");
}

void loop() 
{
  if (number == 1)  //turn left
  {  
    timecount = 0;
    left();
    number = 0;
  }
  else if(number == 2)  //turn right
  {
    timecount = 0;
    right();
    number = 0;
  }
  else if (number == 3) //forward
  {
    timecount = 0;
    forward();
    number = 0;
  }
  
  if (timecount >= 10)  //超過時間無指令就右轉
  {
    timecount = 0;
    right();
    Serial.println("turn right to search");
  }

  stop();
  delay(400);
  timecount++;
}