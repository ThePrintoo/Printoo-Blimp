/***************************************************************************************
* © 2014 YD Ynvisible, S.A.
*
* FileName:        Blimp.ino
* Dependencies:    Servo.h and SoftwareSerial.h 
* Processor:       ATmega328
* IDE:             Arduino 1.0.5
*
* Description:
* Driving a BLIMP (with 2 DC motors + servomotor) through a smartphone via Bluetooth 4.0
* Sending '1', '2', '3' or '4' via a mobile phone terminal allows several controls 
****************************************************************************************/

#include <Servo.h>          //Servo library
#include <SoftwareSerial.h> //Software Serial Port
#define RxD 6
#define TxD 7

SoftwareSerial blueToothSerial(RxD,TxD);
Servo servo1;

int motor1_pwm=11; //Motor1 PWM
int motor1_dir=12; //Motor1 Direction
int motor2_pwm=9;  //Motor2 PWM
int motor2_dir=8;  //Motor2 Direction
char recvChar =0;

void setup()
{
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  pinMode(motor1_pwm, OUTPUT); 
  pinMode(motor1_dir, OUTPUT); 
  pinMode(motor2_pwm, OUTPUT); 
  pinMode(motor2_dir, OUTPUT);
  digitalWrite(motor1_pwm,LOW);
  digitalWrite(motor1_dir,LOW);
  digitalWrite(motor2_pwm,LOW);
  digitalWrite(motor2_dir,LOW);
  
  servo1.attach(14); //analog pin 0
  
  setupBlueToothConnection();
}
void loop()
{ 

  if(blueToothSerial.available()){      //check if the pipe is free
    recvChar = blueToothSerial.read();
    Serial.print(recvChar);
  }
  Servo::refresh();              
  if(recvChar=='1'){
    analogWrite(motor1_pwm,0);     //motor pointing down OFF
    digitalWrite(motor1_dir,LOW);
    analogWrite(motor2_pwm,200);   //back motor ON
    digitalWrite(motor2_dir,LOW);
    servo1.write(90);              //servo at the center 
  }
  if(recvChar=='2'){
    analogWrite(motor1_pwm,0);     //motor pointing down OFF
    digitalWrite(motor1_dir,LOW);
    analogWrite(motor2_pwm,200);   //back motor ON
    digitalWrite(motor2_dir,LOW);
    servo1.write(45);              //servo to the right
  }
  if(recvChar=='3'){
    analogWrite(motor1_pwm,200);   //motor pointing down ON
    digitalWrite(motor1_dir,LOW);
    analogWrite(motor2_pwm,0);     //back motor OFF
    digitalWrite(motor2_dir,LOW);
    servo1.write(90);              //servo at the center        
  }
  if(recvChar=='4'){
    analogWrite(motor1_pwm,0);     //motor pointing down OFF
    digitalWrite(motor1_dir,LOW);
    analogWrite(motor2_pwm,200);   //back motor ON
    digitalWrite(motor2_dir,LOW);
    servo1.write(135);              //servo to the left
  }

}  
  
void setupBlueToothConnection(){
  blueToothSerial.begin(9600); //Set BluetoothBee BaudRate to default baud rate 9600
  delay(10); // This delay is required.
  blueToothSerial.print("AT+RENEW"); //Restore all setup value to factory setup
  delay(10); // This delay is required.
  blueToothSerial.print("AT+ROLE0"); //make it a slave
  delay(10); // This delay is required.
}
//END
