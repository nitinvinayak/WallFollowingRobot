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
   move();

}
void move()
{
  
  
  analogWrite(mpin1,0);
  analogWrite(mpin2,255);
  analogWrite(mpin3,0);
  analogWrite(mpin4,0);
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
  distance=duration*.03412;

  Serial.print("Distance: ");
  Serial.println(distance);
  
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
  distance1=duration1*.03412;

  Serial.print("Distance1: ");
  Serial.println(distance1);
  
  return distance1;
}
