//we declare the ports for the flpidot
int flip=11;
int flop=10;

//we declare the capacitive sensor input
int capSensePin = 2;
//this is the value for the capacitive pin to determine if someone is touching or not 
int touchedCutoff = 15;
//the next values will allow us to do an average of 20 readings of the capacitive sensor
const int numReadings = 20;
int readings[numReadings];
int index = 0;
int total = 0;
int average = 0;
//this is the boolean that tells if the cube is in someones hand
int inHand = false;
//we set the LDR sensor (light sensor) to 0 and declare the analog port for it (A0)
int LDRReading = 0;
int LDR_Pin = A0;
//this is the array in which it will store and play the rythm
unsigned long sequence[40] = {100,1000};
//this is the variable that determines the position in the array
int sequencePosition = 2;

//the two following booleans will help the program to now what to do
boolean touched = false;
boolean record = true;

void setup(){
  Serial.begin(9600);
  pinMode(flip,OUTPUT);
  pinMode(flop,OUTPUT);
}

void loop(){
   
  LDRReading = analogRead(LDR_Pin);                                         //Here we check the readings of the light sensor
  if (LDRReading >= 50 && inHand == false) {                                //Here we check if the Cube is in the user's hand or not (checking the values that come from the light sensor)
    inHand = true;                                                          //If it is in someone's hand, we set the inHand boolean to true and the record boolean to false
    record = false;
    delay(200);
    Serial.println("in hand");
  } else {
  if (LDRReading <= 50 && inHand == true) {
    inHand = false;                                                         //If it is not in someone's hand, we set the inHand boolean to false 
    Serial.println("not in hand");
    delay(200);
} 
  if (inHand){                                                              //Now, if the boolean inHand is True (if it is in someones Hand), firtsly it records.
    if (record){
      
              
      
      total= total - readings[index];                                      //this is the record mode, it will check the capacitive sensor and will record the time when the user presses and releases it.
                                                                           //first, because the capacitive sensor gives us a very unstable signal, we make an averege from the reading. We add twenty readings to eachother and divide them by twenty, then we save them to the "average integer"
      readings[index] = readCapacitivePin(capSensePin); 
      total= total + readings[index];       
      index = index + 1;                    

      if (index >= numReadings){             
        index = 0;                           
        average = total / numReadings;              
      }
      if (average > touchedCutoff && touched == false) {                    //If the capacitive sensor average reads more than the touchCutoff, it will save the time in miliseconds in the sequence array in the position sequencePosition and add one to sequencePosition (this is the position in which it will save the next value)
        touched = true;
        Serial.println("touched");
        sequence[sequencePosition] = millis();
        Serial.print(sequencePosition);
        Serial.print(": ");
        Serial.println(sequence[sequencePosition]);
        sequencePosition++;
        digitalWrite(13,HIGH);
       }
      if (average < touchedCutoff && touched == true){                       //If the capacitive sensor average reads less than the touchCutoff, it will save the time in miliseconds in the sequence array in the position sequencePosition and add one to sequencePosition (this is the position in which it will save the next value)
        touched = false;
        Serial.println("untouched");
        sequence[sequencePosition] = millis();
        Serial.print(sequencePosition);
        Serial.print(": ");
        Serial.println(sequence[sequencePosition]);
        sequencePosition++;
        digitalWrite(13,LOW);
      }                                                                       // we have limited the length of the array to different values, so we can't exceed this length 
      if (sequencePosition == 40){                                            // if it exceeds, we set the position to 0 and the record boolean to false
        record = false;
        Serial.print("too much");
        sequencePosition = 0;
      }

      //Serial.println(average);
    }
    
    else {                                                                     //in this block, we play the rythm 
      if (sequencePosition != 0){                                              //in this "if block", we set to 0 the values in the array that haven't been used (because they may have have been used in the previous rythm)
              Serial.println("here");
              Serial.print(sequencePosition);
              for (int i = sequencePosition; i < 40; i++){
                sequence[i] = 0;
              }
            }
           if (sequence[0] != 0){                                              //in this lock , we play the rythm. first, we set set the record boolean to true so that when it finishes playing, it starts listening.
        for(int i = 0; i <= 40; i++){
          if ((sequence[i] == 0 && i != 0) || i >= 40){
            record = true;
            
            Serial.println("now recording");
            sequencePosition = 0;
          } 
          else {                                                           //here we play the rythm stored in the "sequence" Array
            flipdot(((i & 0x01) == 0));                                    //here we redirect the code to the flipdot function, where the actual "flipping" happens
            //Serial.print(sequence[i+1]);
            //Serial.print(" - ");
            //Serial.print(sequence[i]);
            //Serial.print(" = ");
            //Serial.println(sequence[i+1]-sequence[i]);
            //first we set the duration value to 0, to avoid errors.
            int duration = 0;                                              // in the array we have the time values when de user touched and released the capacitive sensor. So, if the user would have pressed an released the sensor every second, the array would look like this: [1000,2000,3000,4000,5000,6000,.....]                        
            if (sequence[i+1] > sequence[i] && sequence[i+1] != 0)         // Here, we transform this into time values which can be read more easlily and we store them in the duration variable. The array in the exaple would be transformed into this: [1000,1000,1000,1000,1000,....]
              duration = sequence[i+1]-sequence[i];
              
            delay(duration);                                               //this delay is equal to the duration variable (which changes in each loop to the corresponding value of the array)
          }
        }
      }
    }
  }
  
  
}
}

void flipdot(boolean flippy) {                                            //in this function, we flip the flipdot in the opposite direction in which it was 
  if (flippy){
    digitalWrite(flip,HIGH);                                              // dot direction one pin switched to HIGH (+5V)
    digitalWrite(flop,LOW);                                               // dot direction two pin switched to LOW  (GND)
    delay(10);                                                            //quick delay so that the flipdo can flip
    digitalWrite(flip,LOW);
    Serial.println("flip");
  } 
  else {
    digitalWrite(flip,LOW);                                               // dot direction one pin switched to HIGH (+5V)
    digitalWrite(flop,HIGH);                                              // dot direction two pin switched to LOW  (GND)
    delay(10);                                                            //quick delay so that the flipdo can flip
    digitalWrite(flop,LOW);
    Serial.println("flop"); 
  }
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//THIS CODE WILL ALLOW THE PROGRAM TO READ THE CAPACITIVE SENSOR//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// readCapacitivePin
//  Input: Arduino pin number
//  Output: A number, from 0 to 17 expressing
//          how much capacitance is on the pin
//  When you touch the pin, or whatever you have
//  attached to it, the number will get higher
//  In order for this to work now,
// The pin should have a 1+Megaohm resistor pulling
//  it up to +5v.
uint8_t readCapacitivePin(int pinToMeasure){
  // This is how you declare a variable which
  //  will hold the PORT, PIN, and DDR registers
  //  on an AVR
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  // Here we translate the input pin number from
  //  Arduino pin number to the AVR PORT, PIN, DDR,
  //  and which bit of those registers we care about.
  byte bitmask;
  if ((pinToMeasure >= 0) && (pinToMeasure <= 7)){
    port = &PORTD;
    ddr = &DDRD;
    bitmask = 1 << pinToMeasure;
    pin = &PIND;
  }
  if ((pinToMeasure > 7) && (pinToMeasure <= 13)){
    port = &PORTB;
    ddr = &DDRB;
    bitmask = 1 << (pinToMeasure - 8);
    pin = &PINB;
  }
  if ((pinToMeasure > 13) && (pinToMeasure <= 19)){
    port = &PORTC;
    ddr = &DDRC;
    bitmask = 1 << (pinToMeasure - 13);
    pin = &PINC;
  }
  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);
  // Make the pin an input WITHOUT the internal pull-up on
  *ddr &= ~(bitmask);
  // Now see how long the pin to get pulled up
  int cycles = 16000;
  for(int i = 0; i < cycles; i++){
    if (*pin & bitmask){
      cycles = i;
      break;
    }
  }
  // Discharge the pin again by setting it low and output
  //  It's important to leave the pins low if you want to 
  //  be able to touch more than 1 sensor at a time - if
  //  the sensor is left pulled high, when you touch
  //  two sensors, your body will transfer the charge between
  //  sensors.
  *port &= ~(bitmask);
  *ddr  |= bitmask;

  return cycles;
}



