#include <Wire.h>
#include <Kalman.h> // Source: https://github.com/TKJElectronics/KalmanFilter
#include <SoftwareSerial.h>

class Gyro {
private:
  unsigned long timer;
  uint8_t buffer[2];
  double zeroValue[5] = { -200, 44, 660, 52.3, -18.5}; // Found by experimenting TODO add this to calibration phase
  Kalman kalmanX;
  Kalman kalmanY;
  Kalman kalmanZ;
public:
  Gyro ();
  virtual ~Gyro ();
  double getXAngle();
  double getYAngle();
  double getZAngle();
  String toString();
};
