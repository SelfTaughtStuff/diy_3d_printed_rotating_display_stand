/*
 * DIY 3D printed rotating display stand
 * 
 * Created by: Alex Risteski - Svarc
 * Created for: SelfTaughtStuff
 * Channel URL: https://www.youtube.com/@self_taught_stuff
 * 
 * Install "AccelStepper" library
 * More info about the library here: http://www.airspayce.com/mikem/arduino/AccelStepper
 *  
*/

#include <AccelStepper.h>
#define CLK 2
#define DT 3
#define motorPin1  8
#define motorPin2  9
#define motorPin3  10
#define motorPin4  11
#define MotorInterfaceType 8

int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
AccelStepper stepper = AccelStepper(MotorInterfaceType, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  Serial.begin(9600);
  lastStateCLK = digitalRead(CLK);
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);
  stepper.setMaxSpeed(1000);
}

void loop() {
  stepper.setSpeed(counter);
  stepper.runSpeed();
}

void updateEncoder(){
  currentStateCLK = digitalRead(CLK);
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
    if (digitalRead(DT) != currentStateCLK) {
      if(counter > -1000){
        counter -= 10;
      }
      currentDir ="CCW";
    } else {
      if(counter < 1000){
        counter += 10;
      }      
      currentDir ="CW";
    }
    Serial.print("Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Counter: ");
    Serial.println(counter);
  }
  lastStateCLK = currentStateCLK;
}
