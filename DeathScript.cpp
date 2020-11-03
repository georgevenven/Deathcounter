#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <stdlib.h> 
#include <string.h>
#define TIME 700800 

LiquidCrystal lcd(8,9,4,5,6,7);
unsigned long int total = 0; // total time Josh has left to live // lol I totaly forgot that you had to use long 
unsigned long long int lastSecond; 
int daycounter = 0; // for EEPROM mememory (only can be written 10,000 times)
unsigned long long int msec;
bool firstTime = true; 
int retrieval = 0;

void setup()
{  
  lcd.begin(16,2);
  
  EEPROM.get(0, retrieval);

  if (retrieval > 1)
  {
    firstTime = false; 
    for (int i = 0 ; i < EEPROM.length() ; i++) 
    {
      EEPROM.write(i, 0);
    }
  }
}

void loop()
{  
  msec = millis(); // millaseconds since start  

  if (firstTime == false)
  {
    total += retrieval;  
    firstTime = true; // so it doesn't keep adding shit 
  }
   
  if (msec - lastSecond > 1000)
  {
    lastSecond += 1000;
    total++;
  }
  
  if (total % 10 == 0)
  { 
    EEPROM.put(0,total);
  }
  
  lcd.setCursor(0,0);
  lcd.print(TIME - total);
  lcd.setCursor(0,1);
  lcd.print("Hours Left :)");
  delay(100);
}