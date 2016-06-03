#include "MotorController.h"

MotorController::MotorController(){
  //Motor* objArray = static_cast<Motor*>( ::operator new ( sizeof Motor* num_motors ) );
  // invoke constuctors
  for ( int i = 0; i < MOTOR_COUNT; i++ )
    m_motors[i] = new Motor( 10+i , i);//motors start at pin 10 to 13 for a quad copter. TODO: put this in some config or something
};

MotorController::~MotorController(){
  for (size_t i = 0; i < MOTOR_COUNT; i++) {
    m_motors[i]->power(0);//power down all the motors TODO: implement a failure landing procedure here
  }
}
void MotorController::powerMotorsForSpeed(int nominalSpeeds[], int toPower){
  for (size_t i = 0; i < MOTOR_COUNT; i++) {
    int hovering_speed = nominalSpeeds[i];
    //TODO
  }
}
//this should normally take in the stabilizer value for the hovering power of the motor and decrease it by the power demanded (power in %)
void MotorController::powerUpAllMotors(int power){
  for (size_t i = 0; i < (sizeof(m_motors)/sizeof(*m_motors)) ; i++) {
    m_motors[i]->powerUp(power);
  }
}
void MotorController::powerAllMotors(int power){
  for (size_t i = 0; i < (sizeof(m_motors)/sizeof(*m_motors)) ; i++) {
    m_motors[i]->power(power);
  }
}
//this should normally take in the stabilizer value for the hovering power of the motor and decrease it by the power demanded (power in %)

void MotorController::powerDownAllMotors(int power){
  for (size_t i = 0; i < (sizeof(m_motors)/sizeof(*m_motors)) ; i++) {
    m_motors[i]->powerDown(power);
  }
}
int* MotorController::getPowerFromMotors(){
  int res[MOTOR_COUNT];
  for (size_t i = 0; i < MOTOR_COUNT; i++) {
    res[i] = m_motors[i]->getPower();
  }
  return res;
}
