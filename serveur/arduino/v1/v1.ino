#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include "SerialCommand.h"
#include "config.h"

Servo motor_front_right;
Servo motor_front_left;
Servo motor_back_right;
Servo motor_back_left;
int started=FALSE;

SerialCommand sCmd;     // The SerialCommand object

double scale(double valueIn, double baseMin, double baseMax, double limitMin, double limitMax) {
    return ((limitMax - limitMin) * (valueIn - baseMin) / (baseMax - baseMin)) + limitMin;
}
int inbetween(int val,int minv,int maxv){
  return min(maxv, max(minv, val));
}
void decreaseMotor(Servo motor){
  motor.writeMicroseconds(inbetween((motor.readMicroseconds()-10),MIN_PWM_OUTPUT+1,MAX_PWM_OUTPUT));
}
void increaseMotor(Servo motor){
  motor.writeMicroseconds(inbetween((motor.readMicroseconds()+10),MIN_PWM_OUTPUT+1,MAX_PWM_OUTPUT));
}
void calibrate(){
  if(started == TRUE)
    return;//we can't calibrate if we already started
  motor_front_right.writeMicroseconds(MAX_PWM_OUTPUT);
  motor_front_left.writeMicroseconds(MAX_PWM_OUTPUT);
  motor_back_right.writeMicroseconds(MAX_PWM_OUTPUT);
  motor_back_left.writeMicroseconds(MAX_PWM_OUTPUT);

  delay(2500);
  motor_front_right.writeMicroseconds(MIN_PWM_OUTPUT);
  motor_front_left.writeMicroseconds(MIN_PWM_OUTPUT);
  motor_back_right.writeMicroseconds(MIN_PWM_OUTPUT);
  motor_back_left.writeMicroseconds(MIN_PWM_OUTPUT);

}
void land(){
  started=FALSE;
  motor_front_right.writeMicroseconds(MIN_PWM_OUTPUT+100);
  motor_front_left.writeMicroseconds(MIN_PWM_OUTPUT+100);
  motor_back_right.writeMicroseconds(MIN_PWM_OUTPUT+100);
  motor_back_left.writeMicroseconds(MIN_PWM_OUTPUT+100);
  delay(5000);
  motor_front_right.writeMicroseconds(MIN_PWM_OUTPUT);
  motor_front_left.writeMicroseconds(MIN_PWM_OUTPUT);
  motor_back_right.writeMicroseconds(MIN_PWM_OUTPUT);
  motor_back_left.writeMicroseconds(MIN_PWM_OUTPUT);
}
void start(){
  started=TRUE;
  Serial.println("starting");
  motor_front_right.writeMicroseconds(MIN_PWM_OUTPUT+10);
  motor_front_left.writeMicroseconds(MIN_PWM_OUTPUT+10);
  motor_back_right.writeMicroseconds(MIN_PWM_OUTPUT+10);
  motor_back_left.writeMicroseconds(MIN_PWM_OUTPUT+10);
}

void tilt(){
  if(started==FALSE)//check if the quadcopter is started
    return;
  char* dir;
  dir = sCmd.next();    // Get the next argument from the SerialCommand object buffer
  Serial.print("tilting ");
  
  if (dir != NULL ) {    // As long as it existed, take it

    switch (dir[0]) {//take the first char, it will be okey.....
      case 'r':
      case 'R':
        Serial.println("right");
        decreaseMotor(motor_front_right);
        decreaseMotor(motor_back_right);
        increaseMotor(motor_front_left);
        increaseMotor(motor_back_left);

      break;

      case 'l':
      case 'L':
        Serial.println("left");
        increaseMotor(motor_front_right);
        increaseMotor(motor_back_right);
        decreaseMotor(motor_front_left);
        decreaseMotor(motor_back_left);
      break;
    }
  }
}
void rotate()
{
  if(started==FALSE)
    return;
  //copter.setHoveringState(NOT_HOVERING);
  char* dir;
  dir = sCmd.next();    // Get the next argument from the SerialCommand object buffer

  if (dir != NULL) {    // As long as it existed, take it
    switch (dir[0]) {//take the first char, it will be okey.....
      case 'r':
      case 'R':
        decreaseMotor(motor_front_right);
        decreaseMotor(motor_back_left);
        increaseMotor(motor_front_left);
        increaseMotor(motor_back_right);

      break;

      case 'l':
      case 'L':
      //not sure, maybe invert with top if not working
        increaseMotor(motor_front_right);
        increaseMotor(motor_back_left);
        decreaseMotor(motor_front_left);
        decreaseMotor(motor_back_right);
      break;
    }
  }

}

//stabalize the drone for hover mode (stationary flight)
//todo
void hover()
{
  if(started==FALSE)
    return;
  motor_front_right.writeMicroseconds(1200);
  motor_front_left.writeMicroseconds(1200);
  motor_back_right.writeMicroseconds(1200);
  motor_back_left.writeMicroseconds(1200);
}
void throttle(){
//started = TRUE;
  char* per;
  per = sCmd.next();
  if(per!=NULL){
    int percentage = atoi(per);
    //don't actually allow throttle to hit max, and minumum
    int speed = (((MAX_PWM_OUTPUT-MIN_PWM_OUTPUT-100)/100)*percentage)+(MIN_PWM_OUTPUT+50);
    Serial.print("SETTING SPEED TO ");
    Serial.println(speed);
    motor_front_right.writeMicroseconds(speed);
    motor_front_left.writeMicroseconds(speed);
    motor_back_right.writeMicroseconds(speed);
    motor_back_left.writeMicroseconds(speed);
  }
}
void nothin(const char* cmd){
  Serial.println("well there is nothing sir");
}
void setup(){
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  Serial.println("Ready");
  motor_front_right.attach(MOTOR_TOP_RIGHT_PIN);
  motor_front_left.attach(MOTOR_TOP_LEFT_PIN);
  motor_back_right.attach(MOTOR_BACK_RIGHT_PIN);
  motor_back_left.attach(MOTOR_BACK_LEFT_PIN);
  /*Serial.println(MOTOR_TOP_RIGHT_PIN);
  Serial.println(MOTOR_TOP_LEFT_PIN);
  Serial.println(MOTOR_BACK_RIGHT_PIN);
  Serial.println(MOTOR_BACK_LEFT_PIN);*/
  motor_front_right.writeMicroseconds(MIN_PWM_OUTPUT);
  motor_front_left.writeMicroseconds(MIN_PWM_OUTPUT);
  motor_back_right.writeMicroseconds(MIN_PWM_OUTPUT);
  motor_back_left.writeMicroseconds(MIN_PWM_OUTPUT);
  //TODO
  //setup all the motors and their respectiv pins
  //Serial.println("just press something/q to quit this loop");
  /*while(Serial.read() != (int)'q'){
    while(Serial.available() == 0){}

    Serial.println(inbetween(speed,1000,2000));
    delay(300);
  }
  Serial.println("setting up commands");*/
  //setup available commands
  sCmd.addCommand("tilt", tilt);
  sCmd.addCommand("rotate", rotate);
  sCmd.addCommand("throttle",throttle);
  sCmd.addCommand("start",start);
  sCmd.addCommand("land",land);
  sCmd.addCommand("calibrate",calibrate);
  sCmd.setDefaultHandler(nothin);
  //Interput.setup();
  //Compter.setup();

  //copter.start();
  //hover();
}


void loop(){
  sCmd.readSerial();
  //Serial.println("asd");
  delay((1000/CLOCK_SPEED-10));//the clock speed is defined for ESC control 50hz
}
