#include "Motor.h"
Motor::Motor(unsigned short int pin,unsigned short int id){
  m_id=id;
  m_esc.attach(pin);
}

void Motor::power(unsigned short percentage){
  this->setPower(percentage);
}
void Motor::setPower(unsigned short percentage){
  Serial.print("setting power ");
  Serial.print(percentage);
  Serial.print(" on motor");
  Serial.println(m_id);
  m_percentage = percentage;
  sendEscSignal(((MAX_PWM_OUTPUT - MIN_PWM_OUTPUT)*(m_percentage/100))+MIN_PWM_OUTPUT);
}
void Motor::sendEscSignal(unsigned short int sig){
  m_esc.writeMicroseconds(sig);
}
unsigned short int Motor::getPower(){
  return m_percentage;
}
