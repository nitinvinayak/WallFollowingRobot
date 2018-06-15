int mpin1=11;
int mpin2=10;
int mpin3=5;
int mpin4=6;
void setup() {
  pinMode(mpin1,OUTPUT);
  pinMode(mpin2,OUTPUT);
  pinMode(mpin3,OUTPUT);
  pinMode(mpin4,OUTPUT);
    

}

void loop() {
  analogWrite(mpin1,0);
  analogWrite(mpin2,255/2);
  analogWrite(mpin3,0);
  analogWrite(mpin4,255/2);

}
