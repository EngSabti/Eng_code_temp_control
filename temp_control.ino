
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  

#define relay_heater 7

#include "max6675.h"

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
int temp;
int temp_control=0;
void setup() {
  
  Serial.begin(9600);
   lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("Welcome..");
  delay(1000);
    lcd.clear();
    
    pinMode(relay_heater,OUTPUT);
    digitalWrite(relay_heater,1);
}

void loop() {
  int val=analogRead(A0);
  temp_control=map(val,0,1023,0,300);
  temp_control=constrain(temp_control,0,300);
  
 temp= thermocouple.readCelsius();
  
  lcd.setCursor(0,0);
  lcd.print("temp=");
  lcd.print(temp);
  lcd.print("   ");
  
   lcd.setCursor(0,1);
  lcd.print("temp_cont=");
  lcd.print(temp_control);
  lcd.print("   ");
  
  
    
    if(temp>temp_control)
    {
      digitalWrite(relay_heater,1);
    }
    else if(temp<(temp_control-5))
    {
      digitalWrite(relay_heater,0);
    }
    
    
}
