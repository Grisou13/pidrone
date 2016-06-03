#include <Arduino.h>
#include "config.h"
//http://theboredengineers.com/2012/09/the-quadcopter-get-its-orientation-from-sensors/

class Stabilizer {
private:
  int is_stable;
  int m_motor_hovering_speeds[MOTOR_COUNT];
public:
  Stabilizer();
  virtual ~Stabilizer();
  int isStable();
  int getDirection();
  void setHoverringSpeed(int motorSpeeds[MOTOR_COUNT]);
  int* getHoveringSpeed();
  int direction;
};
