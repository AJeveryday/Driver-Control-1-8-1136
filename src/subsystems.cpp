#include "main.h"


namespace flywheel1{
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
