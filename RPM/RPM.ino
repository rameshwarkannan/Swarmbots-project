/* read a rotary encoder with interrupts
   Encoder hooked up with common to GROUND,
   encoder0PinA to pin 2, encoder0PinB to pin 3
   it doesn't matter which encoder pin you use for A or B

   uses Arduino pull-ups on A & B channel outputs
   turning on the pull-ups saves having to hook up resistors
   to the A & B channel outputs

*/

#define encoder0PinA  2  // Encoder Pins
#define encoder0PinB  3



 volatile unsigned int revolutions;
 volatile unsigned int rpm;
 unsigned long timeold;

 
volatile unsigned int encoder0Pos = 0;





 void setup() {

 
 Serial.begin (9600);

pinMode(8,OUTPUT);
digitalWrite(8,HIGH);


  pinMode(encoder0PinA, INPUT_PULLUP);
  pinMode(encoder0PinB, INPUT_PULLUP);


  attachInterrupt(digitalPinToInterrupt(2), doEncoder_Expanded, CHANGE);  // encoder pin on interrupt 0 - pin 2
 attachInterrupt(digitalPinToInterrupt(3), doEncoder_Expanded, CHANGE); 


  //attachInterrupt(digitalPinToInterrupt(3), rpm_fun, CHANGE); 
  
 
   
   
   revolutions = 0;
   rpm = 0;
   timeold = 0;
 
}

void loop() {

  //Serial.println(revolutions);
  
if (revolutions >= 100) { 
     //Update RPM every 12 counts, increase this for better RPM resolution,
     //decrease for faster update
     
     rpm = (30*1000)/(millis() - timeold)*(revolutions/(900)); 
     // Counted rotations of mini wheel for one rotation of large wheel then
     //divided by two (because 30 second interval)
     
     timeold = millis();
     revolutions = 0;
     Serial.println(rpm,DEC);
     
}
     

}


void doEncoder() {
  /* If pinA and pinB are both high or both low, it is spinning
     forward. If they're different, it's going backward.

     For more information on speeding up this process, see
     [Reference/PortManipulation], specifically the PIND register.
  */
  if (digitalRead(encoder0PinA) == digitalRead(encoder0PinB)) {
    encoder0Pos++;
  } else {
    encoder0Pos--;
  }

  //Serial.println (encoder0Pos, DEC);
}

/* See this expanded function to get a better understanding of the
   meanings of the four possible (pinA, pinB) value pairs:
*/
void doEncoder_Expanded() {

revolutions++;
   
  if (digitalRead(encoder0PinA) == HIGH) {   // found a low-to-high on channel A
    if (digitalRead(encoder0PinB) == LOW) {  // check channel B to see which way
      // encoder is turning
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
    else {
      encoder0Pos = encoder0Pos + 1;         // CW
    }
  }
  else                                        // found a high-to-low on channel A
  {
    if (digitalRead(encoder0PinB) == LOW) {   // check channel B to see which way
      // encoder is turning
      encoder0Pos = encoder0Pos + 1;          // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }

  }


}




