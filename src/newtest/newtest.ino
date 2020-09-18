void forward();
void turnleft();
void turnright();
void stopcar();

int trigPinA = 10;   
int echoPinA = 11;    
int trigPinB = 12;
int echoPinB = 13;
float durationA, cmA;
float durationB, cmB;
 
int ENA1=5;
int ENB1=6;
int IN1=2;
int IN2=3;
int IN3=4;
int IN4=7; 


//int x=1500;
float detectdistanceA(){
 
  digitalWrite(trigPinA, LOW); 
  delayMicroseconds(2);   
  digitalWrite(trigPinA,HIGH); 
  delayMicroseconds(10);    
  digitalWrite(trigPinA, LOW); 
  
  durationA = float(pulseIn(echoPinA, HIGH)); 
  
  cmA =  (durationA/2) / 29.1; 

  Serial.print("durationA =");
  Serial.print(durationA);
  Serial.print(" ,cmA = ");
  Serial.print(cmA);
  Serial.println("cm");

  return cmA;
  delay(100);
}
float detectdistanceB(){
 
  digitalWrite(trigPinB, LOW); 
  delayMicroseconds(2);    
  digitalWrite(trigPinB,HIGH); 
  delayMicroseconds(10);    
  digitalWrite(trigPinB, LOW);
  
  durationB = float(pulseIn(echoPinB, HIGH)); 
 
  
  cmB =  (durationB/2) / 29.1; 

  Serial.print("durationB =");
  Serial.print(durationB);
  Serial.print(" ,cmB = ");
  Serial.print(cmB);
  Serial.println("cm");

  return cmB;
  delay(100);
}

void forward(){
  analogWrite(ENA1,200);
  analogWrite(ENB1,200);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  }
void turnback(){
  analogWrite(ENA1,200);
  analogWrite(ENB1,200);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  }
void stopcar(){
  analogWrite(ENA1,0);
  analogWrite(ENB1,0);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  }
  
  void turnright(){
  analogWrite(ENA1,255);
  analogWrite(ENB1,255);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  }
  
void turnleft(){
  analogWrite(ENA1,255);
  analogWrite(ENB1,255);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  }

void setup() 
{
  
  for(int i=2;i<10;i++){
  pinMode(i,OUTPUT);
  }
  Serial.begin(9600);  
  pinMode(trigPinA, OUTPUT);
  pinMode(echoPinA, INPUT);
  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinB, INPUT);

}
void loop() 
{ 
  int x = 100;

  float disA = detectdistanceA();
  float disB = detectdistanceB();
  float ave = (disA + disB)/2;
//  if(disA > 30 || disB > 30){
//    stopcar();
//    turnleft();
//    delay(x/2);
//    forward();
//  }
//  else if(disA > 15){
//    turnleft();
//    delay(x);
//    forward();
//  }
//  else if(disA < 10){
//    turnright();
//    delay(x);
//    forward();
//  }
//  else{
//    forward();
//  }
  if(ave > 10){
    if(disA > disB){
      turnleft();
      delay(2*x);
      forward();
    }
    else{
      stopcar();
      delay(x);
      turnright();
      delay(x/2);
      forward();
    }
  }
  else if(ave < 7){
    if(disA < disB){
      stopcar();
      delay(x/2);
      turnright();
      delay(x*2);
      forward();
    }
    else{
      turnleft();
      delay(x/2);
      forward();
    }
  }
  else{
    forward();
  }
  delay(100);
//  stopcar();
}
