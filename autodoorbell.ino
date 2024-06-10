/*
Project Title: Automatic doorbell
Author: Dan Shan
a doorbell that rings when something is within 5 cm away from it
if distance is over 5 cm but less than 50 the lights will be turned on 
on and "incoming!" will be displayed indicated something is approaching or leaving
trig pin: digital pin 12
echo pin: digital pin 13
LEDs: digital pins 2 through 13
buzzer: in series with LED connected to pin 2
VCC, GND, SDA & SCL pins are wired accordingly
*/

// Include necessary libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD display (16 columns, 2 rows) at I2C address 0x3F
LiquidCrystal_I2C lcd(0x3F, 16, 2);

// Define the pins for the trigger and echo
const int trigPin=12, echoPin=13;

void setup() {
  // Begin the Wire library
  Wire.begin();

  // Begin the LCD
  lcd.begin();

  // Set digital pins 2 through 12 as OUTPUT
  for(int i=2;i<13;i++){
    pinMode(i,OUTPUT);
  }

  // Set the echo pin as INPUT
  pinMode(echoPin, INPUT);

  // Begin the serial communication at 9600 baud rate
  Serial.begin(9600);
}

// Function to blink LEDs based on distance
void blink(int dis){
  // If the distance is less than 6
  if(dis<6){
    // Print "Vistor detected!" on LCD and Serial Monitor
    lcd.print("Visitor detected!");
    Serial.println("Visitor detected!");
  }
  else if(dis<50){
    lcd.print("Incoming!");
    Serial.println("Incoming!");
  }
  else{
    lcd.print("All clear!");
  }

  // Turn on LEDs based on distance
  for(int i=11;i<52;i+=5){ // start at 6 for buzzer otherwise 11 to skip the buzzer
    if(dis<i) digitalWrite(i/5+1,HIGH);
  }

  // Wait for 1 second
  delay(1000);

  // If the distance is less than 6
  if(dis<6){
    // Turn off LED connected to pin 2
    digitalWrite(2, LOW);
  }

  // Turn off LEDs based on distance
  for(int i=6;i<52;i+=5){
    if(dis<i) digitalWrite(i/5+1,LOW);
  }

  // Wait for 1 second
  delay(1000);
}

// Function to display distance on LCD and Serial Monitor
void display(int dis){
  // Print "Distance: " and the distance on Serial Monitor
  Serial.print("Distance: ");
  Serial.println(dis);

  // Print "Distance: " and the distance on LCD
  lcd.print("Distance: ");
  lcd.print(dis);

  // Move the cursor to the beginning of the second line on the LCD
  lcd.setCursor(0,1);
}

// Function to scan the distance
int scan(){
  // Send a short LOW pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(4);

  // Send a 20 microseconds HIGH pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance based on the speed of sound
  int dis = duration*0.0343/2;

  // Return the distance
  return dis;
}

// Main loop
void loop() {
  // Scan the distance
  int dis = scan();

  // Display the distance
  display(dis);

  // Blink LEDs based on distance
  blink(dis);

  // Clear the LCD
  lcd.clear();
}
