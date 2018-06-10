#include <PID_v1.h>

#define mxspd 255
#define factor=255/8
#define kp 10
#define kd 0.5
#define ki 0

int mpin1=11;
int mpin2=10;
int mpin3=5;
int mpin4=6;

double defspd=100;
double spdl;
double spdr;

double setpt = 30;
double distance;

const int trigpin=3;
const int echopin=A0;

long duration;
double ctrlsgnl;

const int trigpin1=9;
const int echopin1=A1;

long duration1;
double distance1;

double distancef;
double distancel;

PID myPID(&distance,&ctrlsgnl,&setpt,kp,kd,ki,DIRECT);


void setup() 
{    
  pinMode(mpin1,OUTPUT);
  pinMode(mpin2,OUTPUT);
  pinMode(mpin3,OUTPUT);
  pinMode(mpin4,OUTPUT);
  
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  pinMode(trigpin1,OUTPUT);
  pinMode(echopin1,INPUT);

  myPID.SetOutputLimits(-100,100);
  myPID.SetMode(AUTOMATIC);
  
  Serial.begin(9600);

}

void loop() {
    distancel=ultsndl();
    if(distancel>100)
    {
      spdl=1.2*0.5*defspd;
      spdr=2*defspd;
      move();
    }
    while(distancel>100)
    {
      distancel=ultsndl();
    }
    distancef=ultsndf();
    if(distancef<20)
    {
      spdl=0;
      spdr=-defspd;
      move();
     
    }
    while(distancef<100)
    {
      distancef=ultsndf();
      spdl=defspd;
      spdr=defspd;
      move();
      
    }
    myPID.Compute();
    if(ctrlsgnl>0)
    {
      spdl=1.2*(defspd+ctrlsgnl);
      spdr=defspd;
    }
    else
    {
      
      spdr=1.2*(defspd-ctrlsgnl);
      spdl=defspd;
    }
    Serial.println(ctrlsgnl);
}
void move()
{
  if (spdr>0)
  {
    analogWrite(mpin1,0);
    analogWrite(mpin2,spdr);
    if (spdl>0)
    {
       analogWrite(mpin3,0);
       analogWrite(mpin4,spdl);
    }
    else
    {
      analogWrite(mpin4,0);
      analogWrite(mpin3,-spdl);
    }
  }
  else
  {
    analogWrite(mpin2,0);
    analogWrite(mpin1,-spdr);
    if (spdl>0)
    {
       analogWrite(mpin3,0);
       analogWrite(mpin4,spdl);
    }
    else
    {
      analogWrite(mpin4,0);
      analogWrite(mpin3,-spdl);
    }
  }
 
}

void stp()
{
  analogWrite(mpin2,0);
  analogWrite(mpin1,0);
  analogWrite(mpin4,0);
  analogWrite(mpin3,0);
}
int ultsndf()
{
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  duration=pulseIn(echopin,HIGH);
  distance=duration*.034/2;
  
  return distance;
}
int ultsndl()
{
  digitalWrite(trigpin1,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin1,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin1,LOW); 
  duration1=pulseIn(echopin1,HIGH);
  distance1=duration1*.034/2;
 
  return distance1;
}
