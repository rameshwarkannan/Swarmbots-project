int refreshRate = 2; // interval at which the RPM refreshes (In seconds)

// These variables are declared volatile because they are used in interrupts, 
// where the variable can be changed at any time, potentially making values in main code innacurate 
volatile int revolutions = 0;
volatile bool rotationDirection; //1=clockwise, 0=counterclockwise

bool beginReading = false; // used in choosing when to count mini wheel pulses

const byte encoderPinA = 2;// These are the pins that the encoder uses to tell you if the wheel is rotating
const byte encoderPinB = 3;// and in what direction. (OUTA and OUTB on pololu page diagram)

const int vccPin = 10; //used to power the encoder logic

const float PPR = 1819.44; // Pulses Per Revolution, how many rotations of small wheel per big wheel
                           // Gear ratio*12*2, Gear ratio * 12 gives PPR (on polulu site)
                           // multiplied by 2 because both encoder pins were given interrupts
                           // Gear ratio used 75.81 (https://www.pololu.com/product/2209)
                           

void setup() {
  
  Serial.begin(9600);
  pinMode(encoderPinA,INPUT_PULLUP); //pullup resistors built into arduino used
  pinMode(encoderPinB,INPUT_PULLUP); // pullup resistors ensure High and Low values are accurate
  
  pinMode(vccPin,OUTPUT);     
  digitalWrite(vccPin,HIGH);

  attachInterrupt(digitalPinToInterrupt(2),rotatingEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(3),rotatingEncoder, RISING);
  
}

void loop() {
  
//Example of using encoder
//Serial.println(findLinearSpeed(findRPM(),4));
//Serial.println(rotationDirection);
//delayMicroseconds(500);

}



// this interrupt function is what counts how many times the mini wheel "pulses"
// it also gives the direction of rotation at the same time
// the direction of rotation is a global variable (rotationDirection) which is changed by the interrupt

void rotatingEncoder(){
  
  //wont count revolutions unless asked
  if(beginReading == true){
    revolutions++;
  }


    // the encoder pins are phase shifted by 90 degrees
    // if pinA leads, it is rotating clockwise
    // if pinB leads, it is rotating counterclockwise
    // this works because the interrupts are triggered only by RISING (low to high)logic
    
if (digitalRead(encoderPinA) == HIGH && digitalRead(encoderPinB) == LOW){
      rotationDirection = true; // clockwise
    }
    else if(digitalRead(encoderPinA) == LOW && digitalRead(encoderPinB) == HIGH){
      rotationDirection = false; // counterclockwise
    }

}




  float findRPM(){
    
  // as soon as you call findRPM(), revolutions start being counted
  beginReading = true;

  // millis() is the amount of time since the program began running (in milliseconds)
  
  float timeOld = millis();
  float rpm = 0.0;

  // the encoder is recording revolutions for as long as "refreshRate" amount of seconds
  while((millis()-timeOld)/1000 <= refreshRate){
   
  }
  
  // now stops recording revolutions
  beginReading = false;

  // rpm = (Pulses recorded/given interval)*(1 Big wheel rotation / Pulses per big wheel rotation, PPR)*(60seconds/1minute)
  rpm = (revolutions*60.0)/PPR;
  

  revolutions = 0;
  return rpm;


 


  
}

float findLinearSpeed(int RPM, int WheelRadius){
  
// formula given by Matt on google doc
float linearSpeed = RPM*WheelRadius*(3.141593/30); // in cm
return linearSpeed;
  
}

float findAngularSpeed(float linearSpeed, float radius, bool isClockwise)
{
  float angularSpeed = linearSpeed/radius;
  return angularSpeed;


}

