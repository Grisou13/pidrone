#include "main.h"
//#include "Copter.h"
//#include "Interupt.h"

SerialCommand sCmd;     // The demo SerialCommand object
Copter copter;
void tilt(){
  copter.setHoveringState(NOT_HOVERING);
  char* dir;
  dir = sCmd.next();    // Get the next argument from the SerialCommand object buffer
  char* per;
  per = sCmd.next();
  if (dir != NULL && per != NULL) {    // As long as it existed, take it
    int percentage = atoi(per);
    switch (dir[0]) {//take the first char, it will be okey.....
      case 'r':
      case 'R':
        copter.tilt(DIRECTION_TILT_RIGHT,percentage);
      break;

      case 'l':
      case 'L':
      copter.tilt(DIRECTION_TILT_LEFT,percentage);
      break;
    }
  }
}
void rotate()
{
  copter.setHoveringState(NOT_HOVERING);
  char* dir;
  dir = sCmd.next();    // Get the next argument from the SerialCommand object buffer
  char* per;
  per = sCmd.next();
  if (dir != NULL && per != NULL) {    // As long as it existed, take it
    int percentage = atoi(per);
    switch (dir[0]) {//take the first char, it will be okey.....
      case 'r':
      case 'R':
        copter.rotate(DIRECTION_ROTATE_RIGHT,percentage);
      break;

      case 'l':
      case 'L':
      copter.rotate(DIRECTION_ROTATE_LEFT,percentage);
      break;
    }
  }

}
void move()
{
  copter.setHoveringState(NOT_HOVERING);
  char* dir;
  dir = sCmd.next();    // Get the next argument from the SerialCommand object buffer
  char* per;
  per = sCmd.next();

  if (dir != NULL && per != NULL) {    // As long as it existed, take it
    int percentage = atoi(per);
    switch (dir[0]) {//take the first char, it will be okey.....
      case 'u':
      case 'U':
        copter.throttle(DIRECTION_MOVE_UP,percentage);
      break;

      case 'd':
      case 'D':
      copter.throttle(DIRECTION_MOVE_DOWN,percentage);
      break;
    }
  }
}
//stabalize the drone for hover mode (stationary flight)
void hover()
{
    copter.hover();//make the copter hover. TODO implement a really hovering copter, right now it just outputs 20% power
}

void throttle()
{
  char* per;
  per = sCmd.next();
  if(per!=NULL)
    copter.setThrottle(atoi(per));
}
void setup(){

  //setup Copter
  sCmd.addCommand("tilt", tilt);
  sCmd.addCommand("hover", hover);
  sCmd.addCommand("move", move);
  sCmd.addCommand("rotate", rotate);
  sCmd.addCommand("throttle",throttle);
  Serial.begin(9600);
  //Interput.setup();
  //Compter.setup();
  Serial.println((1000/CLOCK_SPEED));
  Serial.println();
  Serial.println("Ready");
  copter.start();
  //hover();
}


void loop(){
  sCmd.readSerial();
  delay((1000/CLOCK_SPEED));
  //do clock speed
}
