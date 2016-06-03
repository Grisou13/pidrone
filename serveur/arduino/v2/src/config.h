/*
This file will define most constants for the app, like clock speed, number of motors, etc....
*/
#ifndef CONFIG_H_
#define CONFIG_H_

#define CLOCK_SPEED 50
#define MOTOR_COUNT 4
#define MAX_INCLINE 30 //max 30 deg of incline
#define MAX_ACCEL_SPEED 5 //max 5 m/s of up and down speed

#define MOTOR_TOP_RIGHT_PIN 13
#define MOTOR_TOP_LEFT_PIN 12
#define MOTOR_BACK_RIGHT 11
#define MOTOR_BACK_LEFT 10

#define DIRECTION_MOVE_UP 1
#define DIRECTION_MOVE_DOWN 2

#define DIRECTION_ROTATE_LEFT 1
#define DIRECTION_ROTATE_RIGHT 2

#define DIRECTION_TILT_FORWARD 1
#define DIRECTION_TILT_BACKWARD 2
#define DIRECTION_TILT_RIGHT 3
#define DIRECTION_TILT_LEFT 4

#define DIRECTION_DIAGONAL_UP_RIGHT 1
#define DIRECTION_DIAGONAL_UP_LEFT 2
#define DIRECTION_DIAGONAL_DOWN_RIGHT 3
#define DIRECTION_DIAGONAL_DOWN_LEFT 4

#define IS_STABLE 0
#define IS_NOT_STABLE 1

#define DIRECTION_FALLING 0
#define DIRECTION_CLIMBING 1

#define MIN_PWM_OUTPUT 1000
#define MAX_PWM_OUTPUT 2000

#define HOVERING 0
#define NOT_HOVERING 1

#define DEFAULT_HOVERING_SPEED 20

#define DEBUG 1
/*
class Config{
  public:
    static int getClockSpeedMs() {return int (1000/CLOCK_SPEED);} ;

};*/
#endif
