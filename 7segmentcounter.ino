/*
  Project: LAB: Arduino + Seven Segment Display
  Author: Dan Shan

  Counts from 0 to 9 inclusive using a 7-segment display
  Using a 2d array to store states

  The circuit:
  - pin A connected to output 2
  - pin B connected to output 3
  - pin C connected to output 4
  - pin D connected to output 5
  - pin E connected to output 6
  - pin F connected to output 7
  - pin G connected to output 8
  - pin DP connected to output 9
*/
void setup() {
// connect digital pins to 7-segment display pins.
for(int i=2;i<10;i++) 
pinMode(i, OUTPUT); // connect pin i to output
}
bool arr[10][8]={
{1,1,1,1,1,1,0,0}, // 
{0,1,1,0,0,0,0,0},
{1,1,0,1,1,0,1,0},
{1,1,1,1,0,0,1,0},
{0,1,1,0,0,1,1,0},
{1,0,1,1,0,1,1,0},
{0,0,1,1,1,1,1,0},
{1,1,1,0,0,0,0,0},
{1,1,1,1,1,1,1,0},
{1,1,1,0,0,1,1,0}
};
void loop() {
  // Display every 1 digit for 1 second
  for(int i=0;i<10;i++){
    for(int j=0;j<8;j++){ // display number
      if(arr[i][j]) digitalWrite(j+2,HIGH);
    }
    delay(400);
    for(int j=2; j<9; j++)
      digitalWrite(j, LOW); // reset 
  }
}


