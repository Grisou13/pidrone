#include "Stabilizer.h"

Stabilizer::Stabilizer(){
  is_stable=IS_NOT_STABLE;
  for (size_t i = 0; i < MOTOR_COUNT; i++) {
    m_motor_hovering_speeds[i] = DEFAULT_HOVERING_SPEED;//set default hovering speed to 20%
  }
};
Stabilizer::~Stabilizer(){};
void Stabilizer::setHoverringSpeed(int motorSpeeds[MOTOR_COUNT]){
  for (size_t i = 0; i < MOTOR_COUNT; i++) {
    this->m_motor_hovering_speeds[i] = motorSpeeds[i];
  }
}
int* Stabilizer::getHoveringSpeed(){
  return m_motor_hovering_speeds;
}
int Stabilizer::isStable(){
  //check accèleration, gyro, and compass to determine wether the copter is really stable
  return is_stable;
}
int Stabilizer::getDirection(){
  //checkout the gyro, accel, and magnetometer
  //TODO
  return HOVERING;//just return this for now
}
