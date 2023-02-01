#include "main.h"


namespace intake {

    #define INTAKE_PORT 2
    #define INTAKE_GEARSET E_MOTOR_GEAR_600
    

    extern pros::Motor intake;

    void spin(double pwr);
    void spinForTime(double pwr, int time);
    string getColor();

};
namespace flywheel {

    #define FLYWHEEL_PORT 19
    #define FLYWHEEL_GEARSET E_MOTOR_GEAR_600
    #define LONG_RANGE_POWER 0.6666667
    #define SHORT_RANGE_POWER 0.3333333
    #define MAXIMUM_VOLTAGE 12000
    #define TECHNICAL_FLYWHEEL_RPM 600

    extern pros::Motor motor;

    extern int targetSpeed;
    extern double actualSpeed;

    int voltageUpdate();
    void setTargetSpeed(double pwr);
    void brake(bool mode);

};
namespace odometry {
    extern pros::Rotation leftEncoder;
    extern pros::Rotation rightEncoder;
    extern pros::Rotation backEncoder;
    void odometryController();
    void update();
}