#include "main.h"


namespace intake {

    extern pros::Motor intake;

    void spin(double pwr);
    void spinForTime(double pwr, int time);
    string getColor();

}

namespace flywheel {

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

}

namespace odometry {
    extern pros::Rotation leftEncoder;
    extern pros::Rotation rightEncoder;
    extern pros::Rotation backEncoder;
    void odometryController();
    void update(double linearvel, double turnvel);
    int find_min_angle(double target_heading, double current_heading);
    int move_to_pose_step(int currentPos, double current_heading, int targetPos, double target_heading, double Kp_lin, double Kp_turn, double r, double turnMax, double linMax);
    
}
