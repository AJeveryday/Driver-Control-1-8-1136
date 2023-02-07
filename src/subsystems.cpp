#include "main.h"
#include <iterator>
#include <list>

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
/*
namespace odometry{
    pros::Rotation leftEncoder(1);
    pros::Rotation rightEncoder(2);
    pros::Rotation backEncoder(3);
    pros::Imu imu_sensor(20);
  
    double initX = 0;
    double initY = 0;
    double targetX = 4;
    double targetY = 2.5;
    double currentHeading = imu_sensor.get_heading();
    double targetHeading = 225;
    double tolerance = 0.1;
    double Kp_lin = 20;
    double Kp_turn = 1.7;
    double r = 1;

    auto currentPos = [initX, initY];
    auto targetPos = [targetX, targetY];
    void find_min_angle(double target_heading, double current_heading){
        double turnAngle = targetHeading - currentHeading;
        if (turnAngle > 180 or turnAngle < -180){
            turnAngle = -1 * signbit(turnAngle) * (360 - abs(turnAngle));
        }
    
        return turnAngle;
    }
    void move_to_pose_step(currentPos, currentHeading, targetPos, targetHeading, Kp_lin, Kp_turn, r, turnMax = 100, linMax = 70){
        currentX, currentY = currentPos[0], currentPos(1);
        targetX, targetY = targetPos[0], targetPos[1];
        
        double absTargetAngle = atan2((targetY-currentY), (targetX - currentX)) * 180/3.14159265358979;
    }
    
    
    double wheel_circumference = 4.125 * 3.14159265358979;
    double left_distance, right_distance, back_distance;
    double x_pos, y_pos, theta;
    //constants
    double robothalf = 6.212;
    void odometryController() {
        left_distance = leftEncoder.get_position() * wheel_circumference;
        right_distance = rightEncoder.get_position() * wheel_circumference;
        back_distance = backEncoder.get_position() * wheel_circumference;

        //x_pos = x_pos + (left_distance + right_distance + back_distance) / 3 * cos(theta);
        //y_pos = y_pos + (left_distance + right_distance + back_distance) / 3 * sin(theta);
        
        theta = theta + (right_distance - left_distance) / robothalf*2;//(3 * wheel_circumference)
        y_pos = y_pos + (2 * ((right_distance/theta + robothalf)*(2*(sin((theta/2))))));
        x_pos = x_pos + (2 * ((left_distance/theta + robothalf)*(2*(sin((theta/2))))));
        pros::lcd::print(0, "Odometry: %d\n", x_pos, y_pos, theta);
    }
    void update (){
        odometryController();
    }
    



}
*/

namespace odometry{
    pros::Imu imu_sensor(20);
    double initX = 0;
    double initY = 0;
    double targetX = 4;
    double targetY = 2.5;
    double currentHeading = imu_sensor.get_heading();
    double targetHeading = 225;
    double tolerance = 0.1;
    double Kp_lin = 20;
    double Kp_turn = 1.7;
    double r = 1;
    double pi = 3.14159265359;
    double turnError;
    int current_pos[2] = {initX, initY};
    int target_pos[2] = {targetX, targetY};


    int turn_min_angle(double target_heading, double current_heading){
        double turnAngle = targetHeading - currentHeading;
        if (turnAngle > 180 or turnAngle < -180){
            turnAngle = -1 * signbit(turnAngle) * (360 - abs(turnAngle));
        }
    
        return turnAngle;
    }
    int move_to_pose_step (int currentPos[2], double current_heading, int targetPos[2], double target_heading, double Kp_lin, double Kp_turn, double r = 1, double turnMax = 100, double linMax = 70){
        current_heading = currentHeading;
        target_heading = targetHeading;
        currentPos = current_pos;
        targetPos = target_pos;
        double currentX = currentPos[0];
        double currentY = currentPos[1];
        double targetX = targetPos[0];
        double targetY = targetPos[1];

        double absTargetAngle = atan2((targetY-currentY), (targetX-currentX)) *180/pi;
        if (absTargetAngle < 0){absTargetAngle += 360;};

        double D = sqrt((targetX-currentX)*((targetX-currentX)) + (targetY-currentY)*((targetY-currentY)));
        double alpha = find_min_angle(absTargetAngle, targetHeading);
        double errorTerm1 = find_min_angle(absTargetAngle, currentHeading);

        double beta = atan(r/D) *180/pi;
        if (alpha < 0){
            beta = -beta;
        }
        if (abs(alpha) < abs(beta)){
            turnError = errorTerm1 + alpha;
        }
        else{
            turnError = errorTerm1 + beta;
        }
        double linearVel = Kp_lin * D;
        double turnVel = Kp_turn * turnError;

        bool closeToTarget = false;
        if (D < tolerance){
            closeToTarget = true;
        }
        if(closeToTarget){
            linearVel =  Kp_lin * D * signbit(cos(turnError *pi/180));  
    
            turnError = find_min_angle(targetHeading, currentHeading);
            turnVel = Kp_turn * atan(tan(turnError *pi/180)) *180/pi;
        }   
        if (abs(linearVel) > linMax){linearVel = signbit(linearVel) * linMax;};
            
        if (abs(turnVel) > turnMax){turnVel = signbit(turnVel) * turnMax;};

        if (linearVel > (100 - abs(turnVel))){linearVel = 100 - abs(turnVel);};
            
            
        leftdrive.move(linearVel - turnVel);
        rightdrive.move(linearVel + turnVel);

        //if (abs(leftdrive.get_actual_velocities) > 100){signbit(leftSideVel)*leftSideVel;};
        //if (abs(rightdrive) > 100){signbit(rightSideVel)*rightSideVel;} 
        //double stepDis = (leftSideVel + rightSideVel)/100 * maxLinVelfeet * dt/1000;
        return linearVel, turnVel;
    }
    
}

