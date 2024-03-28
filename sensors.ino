/*
Project: Ultrasonic Distance Sensors
Author: Dan Shan

Scans from sensors printing distance of nearest object
Turns on the pin 4 LED if nothing is within 20 and the pin 3 LED otherwise
process repeats ever 0.1 seconds

The circuit:
 - LED 1 connected to pin 3 (distance < 20)
 - LED 2 connected to pin 4 (distance > 19)
 - trig pin connected to pin 9
 - echo pin connected to pin 10

*/
const int trigPin = 9,echoPin = 10, ledPin1 = 3, ledPin2 = 4;
void setup() {
  // set the modes for the trigger, echo and LED pins:
  pinMode(trigPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(echoPin, INPUT);
  // initialize serial communication:
  Serial.begin(9600);
}
void loop() {
  // take the trigger pin low to start a pulse:
  digitalWrite(trigPin, LOW);
  // delay 2 microseconds:
  delayMicroseconds(4);
  // take the trigger pin high:
  digitalWrite(trigPin, HIGH);
  // delay 10 microseconds:
  delayMicroseconds(20);
  // take the trigger pin low again to complete the pulse:
  digitalWrite(trigPin, LOW);
  // listen for a pulse on the echo pin:
  long duration = pulseIn(echoPin, HIGH);
  // calculate the distance in cm.
  // Sound travels approximately 0.0343 microseconds/cm
  int distance = duration*0.0343/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  if(distance<20) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
  }
  else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, HIGH);
  }
  // a short delay between readings:
  delay(100);
}
