#include "main.h"
#include "pros/adi.hpp"


//MOTORS
pros::Motor intake(2, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);


pros::Motor driveleftfront(3, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driverightfront(16, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor leftmid(5, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightmid(8, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveleftback(17, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driverightback(14, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor flywheel(19, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
//SOLENOID
pros::ADIDigitalOut expansion1('A', false);

//CONTROLLER
pros::Controller controller(pros::E_CONTROLLER_MASTER);
int currentSpeed = 0;
int error= 0;
float Kp = 0.5;
float Ki = 0.1;
float Kd = 0.1;
double targetSpeed = 0;