#include "main.h"

#define FLYWHEEL_GEARSET pros::E_MOTOR_GEARSET_06
#define INTAKE_GEARSET pros::E_MOTOR_GEARSET_06
namespace flywheel{
     pros::Motor motor(FLYWHEEL_PORT, FLYWHEEL_GEARSET);
    
    int targetSpeed = 0;
    double actualSpeed = 0;

    int voltageUpdate() {
        if (targetSpeed == 0)  {motor.move_voltage(0); return 0; }
        actualSpeed = motor.get_actual_velocity();
        int currentVoltage = actualSpeed * (MAXIMUM_VOLTAGE/TECHNICAL_FLYWHEEL_RPM);
        int convertedTarget = targetSpeed * (MAXIMUM_VOLTAGE/TECHNICAL_FLYWHEEL_RPM);
        int error = (convertedTarget - currentVoltage) * 0.5;
        int finalVoltage = convertedTarget + error;
        motor.move_voltage(finalVoltage);
        return finalVoltage;
    };

    void setTargetSpeed(double pwr) {
        targetSpeed = TECHNICAL_FLYWHEEL_RPM * pwr;
        if (targetSpeed > 0) brake(false);
        voltageUpdate();
    };
    void brake(bool mode) {
        if (mode == true && abs(actualSpeed) < 30) motor.set_brake_mode(MOTOR_BRAKE_BRAKE);
        else motor.set_brake_mode(MOTOR_BRAKE_COAST);
    };
}
namespace intake {

    pros::Motor intake(INTAKE_PORT, INTAKE_GEARSET);


    void spin(double pwr) {
        intake.move_voltage(MAXIMUM_VOLTAGE * pwr);
        if (abs(pwr) > 0) flywheel::brake(true); 
        else flywheel::brake(false); 
    };

    void spinForTime(double pwr, int time) {
        intake.move_voltage(pwr);
        pros::delay(time * 1000);
       intake.move_voltage(0);
    };
}
namespace odometry{
    pros::Rotation leftEncoder(1);
    pros::Rotation rightEncoder(2);
    pros::Rotation backEncoder(3);

    double wheel_circumference = 4.125 * 3.14159265358979;
    double left_distance, right_distance, back_distance;
    double x_pos, y_pos, theta;

    void odometryController() {
    left_distance = leftEncoder.get_position() * wheel_circumference;
    right_distance = rightEncoder.get_position() * wheel_circumference;
    back_distance = backEncoder.get_position() * wheel_circumference;

    x_pos = x_pos + (left_distance + right_distance + back_distance) / 3 * cos(theta);
    y_pos = y_pos + (left_distance + right_distance + back_distance) / 3 * sin(theta);
    theta = theta + (right_distance - left_distance) / (3 * wheel_circumference);
    pros::lcd::print(0, "Odometry: %d\n", x_pos, y_pos, theta);
    }
    void update (){
        odometryController();
    }
    void move_to_point(int target_x, int target_y){
        double target_distance = sqrt((x_pos - target_x) * (x_pos - target_x) + (y_pos - target_y) * (y_pos - target_y));
        double target_angle = atan2(target_y - y_pos, target_x - x_pos) - theta;

        chassis.set_drive_pid(target_distance, 110, false, true);
        chassis.set_turn_pid(target_angle, 90);
        pros::delay(20);
    }
    void interference_move_to_point(int targetx, int targety){
        if(chassis.interfered){
            move_to_point(targetx, targety);
            pros::delay(20);
        }
    }
}