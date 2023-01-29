#include "main.h"

//MOTORS
extern pros::Motor intake;


extern pros::Motor driveleftfront;
extern pros::Motor driverightfront;
extern pros::Motor leftmid;
extern pros::Motor rightmid;
extern pros::Motor driveleftback;
extern pros::Motor driverightback;
extern pros::Motor flywheel;
extern pros::ADIDigitalOut expansion1;

//CONTROLLER
extern pros::Controller controller;

extern int currentSpeed;
extern int error;
extern float Kp;
extern float Ki;
extern float Kd;
extern double targetSpeed;