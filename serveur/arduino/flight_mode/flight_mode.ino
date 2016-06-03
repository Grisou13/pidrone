#include <Servo.h>
#define MAX_SIGNAL 2000
#define MIN_SIGNAL 1000
Servo m1;

int val=MIN_SIGNAL;

void setup(){
  Serial.begin(9600);
  Serial.println("calibration, outputting maximumum output");
  m1.attach(10);

  //m1.writeMicroseconds(MIN_SIGNAL);

  Serial.println("Waiting for you now cap");
  /*while (!Serial.available());
  Serial.read();*/

  /*m1.writeMicroseconds(MAX_SIGNAL);
  while (!Serial.available());
  Serial.read();
  Serial.println("Sending minimum output");
  m1.writeMicroseconds(MIN_SIGNAL);*/
}
void loop(){
  if(Serial.available()){
    val = Serial.parseInt();
    //if(val >= MIN_SIGNAL && val <= MAX_SIGNAL){
          
    //}

  }
  m1.writeMicroseconds(val);
  Serial.print("sending ");
  Serial.println(val);  
  delay(17);
}
