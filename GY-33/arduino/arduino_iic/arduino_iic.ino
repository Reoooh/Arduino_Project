#include <i2cmaster.h>

/////////////////////////////////
/*
GY-33-----pro mini 5v 16m
VCC----VCC
CT----A5
DR----A4
GND--GND
S0---GND
*/
/////////////////////////////////
////////////////////////////////
/*
uart 
send 'b'-----Calibration GY-33
send 'a'-----GY33 send data
*/
//////////////////////////////////
#define uint16_t unsigned int
typedef struct
{
    uint16_t Red;
    uint16_t Green;
    uint16_t Blue;
    uint16_t Clear;
} RGB;
unsigned char Re_buf;
unsigned char sign=0;
RGB rgb;
uint16_t CT=0,Lux=0;
byte color=0,rgb_data[3]={0};

void setup() {
       Serial.begin(115200);
       i2c_init();
        delay(1); 
}
void loop() {
  unsigned char data[9]={0};
 if(!sign)
 {
   iic_read(0x00,data,8);
   rgb.Red=(data[0]<<8)|data[1];
   rgb.Green=(data[2]<<8)|data[3];
   rgb.Blue=(data[4]<<8)|data[5];
   rgb.Clear=(data[6]<<8)|data[7];
    Serial.print("Red: ");
   Serial.print(rgb.Red);
   Serial.print(",Green: ");
   Serial.print( rgb.Green);
    Serial.print(",Blue");
    Serial.print( rgb.Blue);
     Serial.print(",Clear");
    Serial.println(rgb.Clear);
    iic_read(0x08,data,4);
     Lux=(data[0]<<8)|data[1];
     CT=(data[2]<<8)|data[3];
   
    Serial.print("CT:");
    Serial.print(CT);
    Serial.print(",Lux:");
    Serial.println( Lux);
     iic_read(0x0c,data,3);
    rgb_data[0]=data[0];
    rgb_data[1]=data[1];
    rgb_data[2]=data[2];
    Serial.print("r:");
    Serial.print( rgb_data[0]);
    Serial.print(",g:"); 
    Serial.print( rgb_data[1]);
    Serial.print(",b:"); 
    Serial.println( rgb_data[2]);
     iic_read(0x0f,data,1); 
     color=data[0];
     Serial.print(",color:"); 
    Serial.println( color,HEX);
 }
 if(sign==1)
 {
   iic_read(0x10,&data[8],1);
   i2c_start_wait(0xb4);
    i2c_write(0x10);
    i2c_write(0x31);
   // i2c_write((data[8]|0x01));
    i2c_stop();
    sign=3;
 }
   delay(200); 
}
void iic_read(unsigned char add,unsigned char *data,unsigned char len)
{
  i2c_start_wait(0xb4);
   i2c_write(add);
   i2c_start_wait(0xb5);
   while(len-1)
   {
    *data++=i2c_readAck();
    len--;
    }
    *data=i2c_readNak();
    i2c_stop();
}
void serialEvent() {
  while (Serial.available()) {   
    Re_buf=(unsigned char)Serial.read();
   if (Re_buf=='a')
       sign=0;
    if (Re_buf=='b')    
       sign=1; 
      Re_buf=0; 
  }
}
