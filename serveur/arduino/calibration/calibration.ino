#include <Servo.h>
#define MAX_SIGNAL 2000
#define MIN_SIGNAL 1000
Servo m1;

void setup(){
  Serial.begin(9600);
  Serial.println("calibration, outputting maximumum output");
  m1.attach(10);
  //m1.attach(11);
  //m1.attach(12);
  //m1.attach(13);
  m1.writeMicroseconds(MAX_SIGNAL);

  Serial.println("Connect esc to battery pack");
  while (!Serial.available());
  Serial.read();
  //delay(3000);
  m1.writeMicroseconds(MIN_SIGNAL);

}
void loop(){
  m1.writeMicroseconds(1000);
  delay(20);
  
}
