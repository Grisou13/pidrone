#include "Motor.h"
#include "config.h"

class MotorController {

public:
  MotorController ();
  virtual ~MotorController ();
  void powerMotorsForSpeed(int* nominalSpeeds,int toPower);
  void powerUpAllMotors(int power);
  void powerDownAllMotors(int power);
  void powerAllMotors(int power);
  int* getPowerFromMotors();
private:
  Motor *m_motors[MOTOR_COUNT];
};
