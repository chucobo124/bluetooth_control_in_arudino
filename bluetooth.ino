#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BTSerial(6, 7); // HC-05的TXD,RXD腳位
SoftwareSerial BTSerial2(3, 2); // HC-05的TXD,RXD腳位

const int ms = 3;
Servo servo[ms];
int mm[ms][2]={
  {5,A0}, 
  {10,A1},
  {11,A2},
};

void init_servo(){
  for (int i = 0 ; i < 3 ;i++ ){
    int mp=mm[i][0]; 
    servo[i].attach(mp);
  }
 }
 
void signal_write(){
  for (int i = 0 ; i < 3 ;i++ ){
   int mp = mm[i][1];
   int val=analogRead(mp);
   val=map(val,0,1023,0,180);
   BTSerial.write(i);
   BTSerial.write(val);
   delay(25);
  }
  
}

void signal_read(){
  for (int i = 0 ; i < 3 ;i++ ){
      int val1 = BTSerial2.read();
      int val2 = BTSerial2.read();
      if (val1 >= 0 && val2 >= 0){
        servo[val1].write(val2);
      }
      delay(20);
  }
}

void setup()
{
  Serial.begin(115200);
  BTSerial.begin(9600);
  BTSerial2.begin(9600);
  init_servo();
}
void loop()
{ 
  //signal_write();
  signal_read();

}
