// Declare all the segments pins
const int pinA = 1;
const int pinB = 2;
const int pinC = 3;
const int pinD = 4;
const int pinE = 5;
const int pinF = 6;
const int pinG = 7;
const int pinDP = 8;
 
int UD = 0;  //read from U/D axis of Joystick
int LR = 0;  //read from L/R axis of Joystick
int curr = pinA;
void setup() {                
  // initialize the digital pins as outputs.

  pinMode(pinA,OUTPUT);
  pinMode(pinB,OUTPUT);
  pinMode(pinC,OUTPUT);
  pinMode(pinD,OUTPUT);
  pinMode(pinE,OUTPUT);
  pinMode(pinF,OUTPUT);
  pinMode(pinG,OUTPUT);
  pinMode(pinDP,OUTPUT);
  Serial.begin(9600);
}

void loop() {

  LR = analogRead(A0);  //read u/d from stick
  UD = analogRead(A1);  //read l/r from stick
 
  Serial.print(curr);

  if(UD>1000)  // send ldown to display if stick is in lower left quadrant
  {
    digitalWrite(curr,LOW);
    if(curr==pinA)
      curr=pinA;
    else if(curr==pinB)
      curr = pinA;
    else if (curr==pinC)
      curr = pinB;
    else if (curr==pinD)
      curr = pinG;
    else if(curr==pinG)
      curr = pinA;
    else if(curr==pinE)
      curr = pinF;
    else if(curr==pinF)
      curr = pinA;
  }
  else if(UD<100)  // send ldown to display if stick is in upper left quadrant
  {
    digitalWrite(curr,LOW);
    if(curr==pinA)
      curr=pinG;
    else if(curr==pinB)
      curr = pinC;
    else if (curr==pinC)
      curr = pinD;
    else if (curr==pinD)
      curr = pinD;
    else if(curr==pinE)
      curr = pinD;
    else if(curr==pinF)
      curr = pinE;
    else if(curr==pinG)
      curr = pinD;    
  }
  else if((UD>500 && UD<600)&&LR<100)
  {
    digitalWrite(curr,LOW);
    if(curr==pinA)
      curr=pinF;
    else if(curr==pinB)
      curr = pinF;
    else if (curr==pinC)
      curr = pinE;
    else if (curr==pinD)
      curr = pinE;
    else if(curr==pinE)
      curr = pinE;
    else if(curr==pinF)
      curr = pinF;
    else if(curr==pinG)
      curr = pinE;   
  }
  else if((UD>500 && UD<600)&&LR>900)
  {
    digitalWrite(curr,LOW);
    if(curr==pinA)
      curr=pinB;
    else if(curr==pinB)
      curr = pinB;
    else if (curr==pinC)
      curr = pinC;
    else if (curr==pinD)
      curr = pinC;
    else if(curr==pinE)
      curr = pinC;
    else if(curr==pinF)
      curr = pinB;
    else if(curr==pinG)
      curr = pinB;   
  }
  digitalWrite(curr,HIGH);
  delay(500);
  
}
