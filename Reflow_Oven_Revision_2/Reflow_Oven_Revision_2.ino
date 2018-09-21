#include "Adafruit_MAX31855.h"

int PeakVar = 1;
int thermoDO = 3;
int thermoCS = 4;
int thermoCLK = 5;
const int relay = 6;   //assigns the relay control to pin 6.
const int start = 7;   //assigns start to pin 7.
const int cancel = 8;  //assigns cancel to pin 8.
int startState = 0;    // assigns startState to 0, will change if push button is pressed.
int cancelState = 0;   // assigns cancelState to 0, will change if push button is pressed.
Adafruit_MAX31855 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup()
{
  Serial.begin(9600); // begins the serial monitor readings.
  pinMode (6, OUTPUT); // sets pin 6 as an output value for the relay.
  pinMode (7, INPUT); // sets pin 7 as an input pin for the start push button.
  pinMode (8, INPUT); // sets pin 8 as an input pin for the cancel push button.
  
  Serial.println ("MAX31855 chip iniztallizing"); // waits for chip to initialize.
  delay(500); // delays for .5 seconds.
}

void preheat()
{
    for (int i=0;i<120;i++) // delays for 120 seconds for preheat time (**edit after finding the time it takes to reach 145 C**)
    {
      if (thermocouple.readCelsius() < 145) // if reading is less than 145 C, turn relay on.
      {
         Serial.print("Internal Temp = ");
  Serial.println(thermocouple.readInternal());
  
  double c = thermocouple.readCelsius();
  if(isnan(c))
  {
    Serial.println("Something is wrong with the thermocouple!");
  }
  else
  {
    Serial.print("C = ");
    Serial.println(c); // prints C in serial monitor.
  }    
  Serial.print("F = ");
  Serial.println(thermocouple.readFarenheit()); // prints F in serial monitor.
  
  delay(200);
        digitalWrite (relay, HIGH);
        delay (1000);
      }
       else
       {
          Serial.print("Internal Temp = ");
  Serial.println(thermocouple.readInternal());
  
  double c = thermocouple.readCelsius();
  if(isnan(c))
  {
    Serial.println("Something is wrong with the thermocouple!");
  }
  else
  {
    Serial.print("C = ");
    Serial.println(c); // prints C in serial monitor.
  }    
  Serial.print("F = ");
  Serial.println(thermocouple.readFarenheit()); // prints F in serial monitor.
  
  delay(200);
        digitalWrite (relay, LOW); // if relay is over 145 C, turn relay off.
        delay (1000);
       }
    }
} 

void peak()
{

  for (int i=0;i<45;i++) //Ramp-to-Peak stage, set to 45 seconds (**edit after finding the time it takes to reach 217 C**)
  {
    if (thermocouple.readCelsius() < 217) // If reading is less than 217 C, turn relay on.
    {
       Serial.print("Internal Temp = ");
  Serial.println(thermocouple.readInternal());
  
  double c = thermocouple.readCelsius();
  if(isnan(c))
  {
    Serial.println("Something is wrong with the thermocouple!");
  }
  else
  {
    Serial.print("C = ");
    Serial.println(c); // prints C in serial monitor.
  }    
  Serial.print("F = ");
  Serial.println(thermocouple.readFarenheit()); // prints F in serial monitor.
  
  delay(200);
      digitalWrite (relay, HIGH);
      delay (1000);
    }
    else
    {
       Serial.print("Internal Temp = ");
  Serial.println(thermocouple.readInternal());
  
  double c = thermocouple.readCelsius();
  if(isnan(c))
  {
    Serial.println("Something is wrong with the thermocouple!");
  }
  else
  {
    Serial.print("C = ");
    Serial.println(c); // prints C in serial monitor.
  }    
  Serial.print("F = ");
  Serial.println(thermocouple.readFarenheit()); // prints F in serial monitor.
  
  delay(200);
     digitalWrite (relay, LOW); // If reading is more than 217 C, turn relay off.
     delay (5000);
    }
  }
}

void otherPeak(){
  while(PeakVar = 1){
    {
       Serial.print("Internal Temp = ");
  Serial.println(thermocouple.readInternal());
  
  double c = thermocouple.readCelsius();
  if(isnan(c))
  {
    Serial.println("Something is wrong with the thermocouple!");
  }
  else
  {
    Serial.print("C = ");
    Serial.println(c); // prints C in serial monitor.
  }    
  Serial.print("F = ");
  Serial.println(thermocouple.readFarenheit()); // prints F in serial monitor.
  
  delay(200);
      if(thermocouple.readCelsius() < 217){
        digitalWrite (relay, HIGH);
        delay (1000);
      }
      else
      {
         Serial.print("Internal Temp = ");
  Serial.println(thermocouple.readInternal());
  
  double c = thermocouple.readCelsius();
  if(isnan(c))
  {
    Serial.println("Something is wrong with the thermocouple!");
  }
  else
  {
    Serial.print("C = ");
    Serial.println(c); // prints C in serial monitor.
  }    
  Serial.print("F = ");
  Serial.println(thermocouple.readFarenheit()); // prints F in serial monitor.
  
  delay(200);
        PeakVar=0;  //If it is not less than 217, break loop
        delay(5000); //Hold it 5 seconds
      }
    }
  }
}


void cool()
{
  digitalWrite(relay, LOW); // turns off relay to start cool stage.
}

void loop()
{
 
  startState = digitalRead(start);   // starts reading pin 7.
  cancelState = digitalRead(cancel); // starts reading pin 8.

  Serial.print("Internal Temp = ");
  Serial.println(thermocouple.readInternal());
  
  double c = thermocouple.readCelsius();
  if(isnan(c))
  {
    Serial.println("Something is wrong with the thermocouple!");
  }
  else
  {
    Serial.print("C = ");
    Serial.println(c); // prints C in serial monitor.
  }    
  Serial.print("F = ");
  Serial.println(thermocouple.readFarenheit()); // prints F in serial monitor.
  
  delay(200);
  
  if (startState == HIGH) // If start button is pressed, start reflow process.
  {
    preheat();
    delay (500);
    peak();
    delay (500);
    cool();
   }
  else if(cancelState == HIGH) // If cancel button is pressed, stop reflow process.
  {
    digitalWrite (relay, LOW);
  }
}
