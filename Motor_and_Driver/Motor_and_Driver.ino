//MOTOR AND DRIVER CODE:
//ONE: LEFT WHEEL
//TWO: RIGHT WHEEL
//BAUD: 9600


//Encoder ONE
const int vccPinONE = 3;
const int phasePinONE = 4;
const int enablePinONE =5;

//Encoder TWO

const int vccPinTWO = 6;
const int phasePinTWO = 7;
const int enablePinTWO = 8;


int wheelSpeed = 100;



void setup() {


Serial.begin(9600);

//Encoder 1 Pins
pinMode(vccPinONE, OUTPUT);
digitalWrite(vccPinONE,HIGH);

pinMode(phasePinONE, OUTPUT);
digitalWrite(phasePinONE, LOW);

pinMode(enablePinONE, OUTPUT);
digitalWrite(enablePinONE, LOW);




//Encoder 2 Pins
pinMode(vccPinTWO, OUTPUT);
digitalWrite(vccPinTWO,HIGH);

pinMode(phasePinTWO, OUTPUT);
pinMode(phasePinTWO, LOW);

pinMode(enablePinTWO,OUTPUT);
digitalWrite(enablePinTWO,LOW);







   
}

void loop() {
  // put your main code here, to run repeatedly:







}
   


//directions based on truth table on driver page:
// https://www.pololu.com/product/2990

void goFwdFull()
{ 
    digitalWrite(phasePinONE,LOW);
    digitalWrite(phasePinTWO,LOW);
    analogWrite(enablePinONE,255);
    analogWrite(enablePinTWO,255);
} 
 void goFwdHalf() 
 { 
    digitalWrite(phasePinONE,LOW);
    digitalWrite(phasePinTWO,LOW);
    analogWrite(enablePinONE,123);
    analogWrite(enablePinTWO,123);
 }


 void goBackFull() 
 { 
    digitalWrite(phasePinONE,HIGH);
    digitalWrite(phasePinTWO,HIGH);
    analogWrite(enablePinONE,255);
    analogWrite(enablePinTWO,255);

 }
 void goBackHalf() // two wheels at half instead of one wheel at full
 { 
    digitalWrite(phasePinONE,HIGH);
    digitalWrite(phasePinTWO,HIGH);
    analogWrite(enablePinONE,123);
    analogWrite(enablePinTWO,123);
 } 
  void Stop() 
  {
    digitalWrite(phasePinONE,LOW);
    digitalWrite(phasePinTWO,LOW);
    analogWrite(enablePinONE,0);
    analogWrite(enablePinTWO,0);
  } 
  void spinCounterClockwise() 
  {
    digitalWrite(phasePinONE,LOW);
    digitalWrite(phasePinTWO,HIGH);
    analogWrite(enablePinONE,255);
    analogWrite(enablePinTWO,255);
  } 
  void spinClockwise() 
  {
    digitalWrite(phasePinONE,HIGH);
    digitalWrite(phasePinTWO,LOW);
    analogWrite(enablePinONE,255);
    analogWrite(enablePinTWO,255);
  }
   void turnSoftRight() {
    
      digitalWrite(phasePinONE,LOW);
    digitalWrite(phasePinTWO,LOW);
    analogWrite(enablePinONE,255);
    analogWrite(enablePinTWO,200);
    
    }
 void turnSoftLeft() 
 { 
    digitalWrite(phasePinONE,LOW);
    digitalWrite(phasePinTWO,LOW);
    analogWrite(enablePinONE,200);
    analogWrite(enablePinTWO,255);
 }
  
