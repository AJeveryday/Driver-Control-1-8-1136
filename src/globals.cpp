#include "main.h"
#include "globals.hpp"
#include "pros/adi.hpp"

namespace port {
    // !                                                !
    //  TO VIEW AND EDIT PORT NUMBERS, GO TO GLOBALS.HPP
    // !                                                !
}

//DRIVE MOTORS
pros::Motor driveleftfront(port::lf, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driverightfront(port::rf, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor leftmid(port::lm, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightmid(port::rm, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveleftback(port::lb, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driverightback(port::rb, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::MotorGroup leftdrive({driveleftfront,leftmid, driveleftback});
pros::MotorGroup rightdrive({driverightfront,rightmid, driverightback});


//SOLENOID
pros::ADIDigitalOut expansion1('A', false);

//CONTROLLER
pros::Controller controller(pros::E_CONTROLLER_MASTER);