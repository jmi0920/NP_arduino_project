/*
  Relay attached from pin 13 to ground 
  pushbutton attached to pin 2 & 3 from +5V
  10K resistor attached to push button from ground
 */

\
const int start = 2;   
const int relay =  13;
const int cancel = 3;

// variable for reading the pushbutton status
int startState = 0;         
int cancelState = 0;

void setup() 
  {
  pinMode(relay, OUTPUT);      
  pinMode(start, INPUT);     
  pinMode(cancel, INPUT);
  }

void loop()
  {
  // read the state of the pushbutton value:
  startState = digitalRead(start);
  cancelState = digitalRead(cancel);

  if (startState == HIGH) 
  {     
    // turn relay on:    
    digitalWrite(relay, HIGH);  
  } 
 if (cancelState == HIGH)
  {
    // turn relay off:
    digitalWrite(relay, LOW); 
  }
}

