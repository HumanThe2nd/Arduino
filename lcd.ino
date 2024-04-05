// Project: I2C 16x2 LCD
// Author: Dan Shan
// prints Hello world! on the first line of the lcd
// prints Goodbye world! on the second line of the lcd
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
void setup()
{
Wire.begin();
lcd.begin();
lcd.print("Hello World!");
lcd.setCursor(0,1); // move to row 2 column 1
lcd.print("Goodbye world!");
lcd.backlight();
Serial.begin(9600);
Serial.println("\nI2C Scanner");
}
void loop()
{
byte error, address;
int Devices;
Serial.println("Scanning...");
Devices = 0;
for(address = 1; address < 127; address++ )
{

Wire.beginTransmission(address);
error = Wire.endTransmission();
if (error == 0)
{
Serial.print("I2C device found at address 0x");
if (address<16)
Serial.print("0");
Serial.print(address,HEX);
Serial.println("  !");
Devices++;
}
else if (error==4)
{ // gets icd port if it exists
Serial.print("Unknown error at address 0x");
if (address<16)
Serial.print("0");
Serial.println(address,HEX);
}
}
if (Devices == 0)
Serial.println("No I2C devices found\n");
else
Serial.println("done\n");
delay(5000);          
}
