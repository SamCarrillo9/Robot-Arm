#include <Servo.h>

Servo armServo1, armServo2, baseServo, clawServo;
int button = A0;
int x = A1;
int y = A2;
int pot = A3;
int pot2 = A4;

int xposition = 90;
int yposition = 90;
int basePosition = 90;
int clawValue = 90;
int direction = 1;
bool clawClosing = true;
bool holding = false;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  armServo1.attach(8);
  armServo1.write(140);
  armServo2.attach(9);
  armServo2.write(180);
  baseServo.attach(10);
  baseServo.write(90);


  clawServo.attach(11);
  clawServo.write(90);
}


void loop() {
  int xval = analogRead(x);
  int yval = analogRead(y);
  int potVal = analogRead(pot);
  int button = analogRead(button);
  int potVal2 = analogRead(pot2);
 
  xval = map(xval, 0, 1023, 0, 180); // scale it to use it with the servo (value between 0 and 180)
  yval = map(yval, 0, 1023, 180, 0);
  potVal = map(potVal, 0, 1023, 160, 0);
  potVal -= potVal % 3;
  potVal2 = map(potVal2, 0, 1023, 180, 90);

  Serial.print(yposition);
  Serial.print(" - ");
  Serial.print(xposition);
  Serial.print(" - ");
  Serial.print(clawValue);
  Serial.print(" - ");
  Serial.print(holding);
  Serial.print(" - ");
  Serial.print(potVal2);
  Serial.println("");

  if(xval >= 85 && xval <= 95){
    xval = 90;
  }
  if(yval >= 85 && yval <= 95){
    yval = 90;
  }
  ///////////////////////

  if(xval > 90 && xposition < 180 && xval > yval && xval > 180 - yval){
    armServo1.write(xposition+=1);
  }
  else if(xval < 90 && xposition > 0 && xval < yval && xval < 180 - yval){
   armServo1.write(xposition-=1);
  }
 
  ///////////////////////
 
  if(yval > 90 && yposition < 180 && yval > xval && yval > 180 - xval){
    armServo2.write(yposition+=1);
  }
  else if(yval < 90 && yposition > 0 && yval < xval && yval < 180 - xval){
    armServo2.write(yposition-=1);
  }
  ///////////////////////
  
  baseServo.write(potVal);
  clawServo.write(potVal2);
  delay(10);
}
