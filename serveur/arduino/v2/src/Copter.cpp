#include "Copter.h"
#include <SoftwareSerial.h>
Copter::Copter(){
  /*this->m_motors = new MotorController();
  this->m_stabilizer = new Stabilizer();*/
};
Copter::~Copter(){
  m_motors.powerAllMotors(0);
};
void Copter::start(){
  m_motors.powerAllMotors(0);//the esc ask for the signal to start at the minimum, otherwise it consideres the craft is disconnected and go in safe mode
  m_motors.powerAllMotors(50);//just give it a little nod
  delay(500);//fly for 0.5s at 50% speed and then make the craft hover
  //normally we should use the stablilizer to get the altitude travelled
  //and at a certain altitude, let the copter stabilize

  //we make it stabilize only if we managed to handle the copter
  if(!DEBUG)
    hover();//make it hover
}
void Copter::hover(){
  setHoveringState(HOVERING);
  while(isHovering() && m_stabilizer.isStable()!=IS_STABLE){
    Serial.println("hovering");
    switch(m_stabilizer.getDirection()){
      default:
        m_motors.powerAllMotors(DEFAULT_HOVERING_SPEED);//just for now, put the motors on 50%, this should be calculated with the stabilizer
        break;
    }
    if(m_stabilizer.isStable() == IS_STABLE)
      m_stabilizer.setHoverringSpeed(m_motors.getPowerFromMotors());//we finally managed to stabilize the drone, so we can extract the speed of the motors to determine the power at which the copter is stable

  }
}
//more elegant way of throttling
void Copter::throttle(int direction, int percentage){
  int* hoverSpeeds;
  hoverSpeeds = m_stabilizer.getHoveringSpeed();
  switch (direction) {
    case DIRECTION_MOVE_UP:
      m_motors.powerMotorsForSpeed(hoverSpeeds,percentage);
    break;
    case DIRECTION_MOVE_DOWN:
      m_motors.powerMotorsForSpeed(hoverSpeeds, percentage);
    break;
  }
}
//make the copter rotate
void Copter::rotate(int direction, int percentage){
  setHoveringState(NOT_HOVERING);
  switch (direction) {
    case DIRECTION_ROTATE_RIGHT:
    break;
  }
}
//make the copter tilt
void Copter::tilt(int direction, int percentage){
  setHoveringState(NOT_HOVERING);
  switch (direction) {
    case DIRECTION_TILT_FORWARD:
      //get the max allowed tilt
      //get the current tilt
      //see how much is the percentage asked for the main tilt
      //tilt(percentage - (max-current/max * 100))
    break;
  }
}
void Copter::setHoveringState(unsigned short int state){
  //TODO maybe a loop that checks wether the stabilizing loop has been stopped
  this->m_hovering_state = state;
}
//determine wether the copter is hovering
unsigned short int Copter::isHovering(){
  return m_hovering_state == HOVERING;
}

//directly sets the throttle for the motors
void Copter::setThrottle(unsigned int prc){
  m_motors.powerAllMotors(prc);
}
/*
@return int Status of the tilt (1 ERROR, 0 OK)
*/
/*
int tilt(int _direction=Copter::TILT_FORWARD){
  switch(dir){
    case Copter::TILT_FORWARD:
    break;
    default:
      return 1;
    break
  }
  return 1;
}
int rotate(int _direction = Copter::MOVE_RIGHT)
{

}
int dive(int _direction = Copter::MOVE_UP)
{

}
//stabalize the drone for hover mode (stationary flight)
int hover(int _direction = Copter::DONT_MOVE)
{

}
*/
