/////////////////////
/*
GY-33软件串口代码
GY33----MINI
VCC----VCC
GND----GND
1:GY33_TX---10,
2:GY33_RX---11,send A5 01 A6 to GY-33
*/
//////////////////
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // arduino-RX, arduino-TX

unsigned char Re_buf[11],counter=0;
unsigned char sign=0;
byte rgb[3]={0};
void setup() {
   Serial.begin(9600);
   mySerial.begin(9600);
   mySerial.listen();  
   delay(10);    
   mySerial.write(0XA5); 
   mySerial.write(0X01);    //初始化,连续输出模式
   mySerial.write(0XA6);    //初始化,连续输出模式
} 

void loop() {
  unsigned char i=0,sum=0;
  while (mySerial.available()) {   
    Re_buf[counter]=(unsigned char)mySerial.read();
    if(counter==0&&Re_buf[0]!=0x5A) return;      // 检查帧头         
    counter++;       
    if(counter==8)                //接收到数据
    {    
       counter=0;                 //重新赋值，准备下一帧数据的接收 
       sign=1;
    }      
  }
  if(sign)
  {   
     sign=0;
     for(i=0;i<7;i++)
      sum+=Re_buf[i]; 
     if(sum==Re_buf[i] )        //检查帧头，帧尾
     {  	       
          rgb[0]=Re_buf[4];
          rgb[1]=Re_buf[5];
          rgb[2]=Re_buf[6];
           Serial.print("r:");
           Serial.print( rgb[0]);
           Serial.print(",g:");
           Serial.print( rgb[1]);
           Serial.print(",b:");
           Serial.println( rgb[2]);
           
   }
  } 

}

