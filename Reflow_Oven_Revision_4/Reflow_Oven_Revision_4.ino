#include "Adafruit_MAX31855.h"
#include <LiquidCrystal.h>

int thermoDO = 3;
int thermoCS = 4;
int thermoCLK = 5;
const int relay = 6;   //assigns the relay control to pin 6.
const int start = 7;   //assigns start to pin 7.
const int cancel = 8;  //assigns cancel to pin 8.
int startState = 0;    // assigns startState to 0, will change if push button is pressed.
int cancelState = 0;   // assigns cancelState to 0, will change if push button is pressed.
Adafruit_MAX31855 thermocouple(thermoCLK, thermoCS, thermoDO);
LiquidCrystal lcd(1, 2, 9, 10, 11, 12); // initailizes LCD pins. 

void setup()
{
  Serial.begin(9600); // begins the serial monitor readings.
  pinMode (6, OUTPUT); // sets pin 6 as an output value for the relay.
  pinMode (7, INPUT); // sets pin 7 as an input pin for the start push button.
  pinMode (8, INPUT); // sets pin 8 as an input pin for the cancel push button.
  lcd.begin(16, 2); // sets up the LCD's number of columns and rows.
  lcd.print("MAX31855 test");
  Serial.println ("MAX31855 chip iniztallizing"); // waits for chip to initialize.
  delay(500); // delays for .5 seconds.
}

void preheat()
{
    for (int i=0;i<15;) 
    {
      if (thermocouple.readCelsius() < 120) 
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
        lcd.setCursor(0,0); // sets begining point of LCD screen at 0,0
        lcd.print("C = ");  // prints "C =" on LCD screen. 
        lcd.println(c);     // prints Celsius reading on LCD screen.
        
        delay(200);
        digitalWrite (relay, HIGH);
        delay (500);
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
          digitalWrite (relay, LOW); 
          i++;
          delay (500);
       }
   }
} 

void peak()
{

  for (int i=0;i<10;) //Ramp-to-Peak stage, set to 45 seconds 
  {
    if (thermocouple.readCelsius() < 175) // If reading is less than 175 C, turn relay on.
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
      lcd.setCursor(0,0);
      lcd.print("C = ");
      lcd.print(c);
      
      delay(200);
      digitalWrite (relay, HIGH);
      delay (500);
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
    digitalWrite (relay, LOW); // If reading is more than 175 C, turn relay off.
    i++;
    delay (500);
    }
  }
}

void cool()
{
  digitalWrite(relay, LOW); // turns off relay to start cool stage.
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
   lcd.setCursor(0,0);
   lcd.print("C = ");
   lcd.print(c);
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
