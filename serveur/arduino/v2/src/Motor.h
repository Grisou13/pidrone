#ifndef Motor_h
#define Motor_h

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include "config.h"
class Motor
{
  public:
    Motor(unsigned short int pin,unsigned short int id);
    volatile ~Motor();
    void powerUp(unsigned short int percentage);//set power / 2
    void powerDown(unsigned short int percentage); //set power/2
    void power(unsigned short int percentage);
    unsigned short int getPower();
    unsigned short int getId();
  private:
    void setPower(unsigned short int percentage);
    void sendEscSignal(unsigned short int sig);
    int m_actual_power;
    unsigned short m_percentage;
    Servo m_esc;
    unsigned short int m_id;
};

#endif //end MOTOR_H
