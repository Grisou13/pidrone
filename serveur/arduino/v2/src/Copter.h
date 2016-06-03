#include <Arduino.h>
#include "config.h"
#include "Gyro.h"
#include "Motor.h"
#include "MotorController.h"
#include "Accel.h"
#include "Compass.h"
#include "Stabilizer.h"
class Copter {
private:
  /* data */
public:
  Copter ();
  virtual ~Copter ();
  void tilt(int direction,int percentage);
  void throttle(int direction,int percentage);
  void setThrottle(unsigned int prc);
  void rotate(int direction,int percentage);
  void hover();
  void correct(int direction,int percentage);
  void start();
  unsigned short int isHovering();
  void setHoveringState(unsigned short state);
  void interruptHovering();
private:
  MotorController m_motors;
  Stabilizer m_stabilizer;
  unsigned short int m_hovering_state = NOT_HOVERING;
};
/*
SerialCommand sCmd;     // The demo SerialCommand object
void setup(){
  //setup interupts
  Serial.begin(9600);

  // Setup callbacks for SerialCommand commands
  sCmd.addCommand("get",   get_data);
  sCmd.addCommand("set",   set_data);
  sCmd.addCommand("tilt", tilt);
  sCmd.addCommand("move",     move);
  sCmd.addCommand("rotate",     rotate);

  sCmd.setDefaultHandler(unrecognized);      // Handler for command that isn't matched  (says "What?")
}
void get_data(){
  char *resource = sCmd.next();

  char *id = sCmd.next();

  if(id == NULL && resource == NULL)
    Serial.println("not enough args for get resource");

  serial.println(Copter.getResource(resource)[id].toString());


}
void unrecognized(const char *command){
  Serial.print("error command ");
  Serial.print(command);
  Serial.println("not found")
}
*/
