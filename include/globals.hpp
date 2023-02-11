#include "main.h"
#include "subsystems.hpp"

namespace port {

    const int flywheel = 19;
    const int intake = 15;

    const int lf = 11;
    const int rf = 9;
    const int lm = 5;
    const int rm = 6;
    const int lb = 18;
    const int rb = 8;

    const int radio = 0;
    const int IMU = 0;

}

//MOTORS
extern pros::Motor driveleftfront;
extern pros::Motor driverightfront;
extern pros::Motor leftmid;
extern pros::Motor rightmid;
extern pros::Motor driveleftback;
extern pros::Motor driverightback;

extern pros::ADIDigitalOut expansion1;

//CONTROLLER
extern pros::Controller controller;

extern pros::MotorGroup leftdrive;
extern pros::MotorGroup rightdrive;
