#include "main.h"
#include "pros/misc.h"
#include "globals.hpp"


///
// Constants
///


///
// Drive Example
///

// . . .
// Make your own autonomous functions here!
// . . .





/*
void autonflywheel(int rpm) {
  //rpm = rpm/6;
  flywheel.move_velocity(rpm);
  currentSpeed = flywheel.get_actual_velocity();
  targetSpeed = currentSpeed/2;
  while(true){
    currentSpeed = flywheel.get_actual_velocity();
    error = targetSpeed- currentSpeed;
    float P = error * Kp;
    float I = error * Ki;
    float D = error * Kd;
    int output = P+I+D;
    flywheel.move_velocity(output);
    pros::delay(20);
  }
};

void intakeon() {
  intake.move_velocity(180);
};

void intakeoff() {
  intake.move_velocity(0);
};

void autonroller() {
  intake.move_velocity(-200);
  pros::delay(500);
  intake.move_velocity(0);
};

void autonindex(int time) {
  intake.move_velocity(-200);
  pros::delay((time*400));
  intake.move_velocity(1);
};

/*
void autonright() {
  
  autonflywheel(flywheel_start);
  chassis.set_drive_pid(-23.4, DRIVE_SPEED, true);  // Move 23.4 inches backward
  chassis.wait_drive(); 
  chassis.set_turn_pid(90, TURN_SPEED);               // Turn 90 degrees clockwise
  chassis.wait_drive();
  chassis.set_drive_pid(-6, DRIVE_SPEED, true);     // Move 5 inches backward
  chassis.wait_drive();
  autonroller();
  chassis.wait_drive(); /*
  chassis.set_turn_pid(-(10), TURN_SPEED);             // Turn R1 degrees clockwise
  chassis.wait_drive();
  autonindex(2);
  chassis.set_turn_pid(-(45+R1), TURN_SPEED);       // Turn 45+R1 degrees counterclockwise
  chassis.wait_drive();
  chassis.set_drive_pid(17, DRIVE_SPEED, true);     // Move 17 inches forward
  chassis.wait_drive();
  intakeon();
  chassis.set_drive_pid(33.1, DRIVE_SPEED, true);   // Move 33.1 inches forward
  chassis.wait_drive();
  intakeoff();
  chassis.set_turn_pid((90-R2), TURN_SPEED);        // Turn 90-R2 degrees clockwise
  chassis.wait_drive();
  autonindex(2);
  
}


void autonleft1() {
  autonflywheel(flywheel_start);
  chassis.set_drive_pid(-3, DRIVE_SPEED, true);
  autonroller();
  chassis.set_drive_pid(5, DRIVE_SPEED, true);      // Move forward 5 inches
  chassis.wait_drive(); 
  autonindex(2);
  chassis.set_turn_pid((45), TURN_SPEED);           // Turn 45+ degrees clockwise
  chassis.wait_drive();
  chassis.set_drive_pid(17, DRIVE_SPEED, true);     // Move forward 17 inches
  chassis.wait_drive();
  intakeon();
  chassis.set_drive_pid(33.1, DRIVE_SPEED, true);   // Move forward 33.1 inches
  chassis.wait_drive();
  intakeoff();
  chassis.set_turn_pid(-(90-L1), TURN_SPEED);       // Turn 90-L1 degrees counterclockwise
  chassis.wait_drive();
  autonindex(3);
  chassis.set_turn_pid((90-L1), TURN_SPEED);        // Turn 90-L1 degrees clockwise
  chassis.wait_drive();
  intakeon();
  chassis.set_turn_pid(18, DRIVE_SPEED);            // Move forward 18 inches
  intakeoff(); //
};



void autonselfawpleft() {
  autonflywheel(flywheel_start);
  autonroller();
  chassis.set_drive_pid(5, DRIVE_SPEED, true);      // Move forward 5 inches
  chassis.wait_drive();
  chassis.set_turn_pid(-L1, TURN_SPEED);            // Turn R1 degrees counterclockwise
  chassis.wait_drive();
  autonindex(2);
  chassis.set_turn_pid((45+L1), TURN_SPEED);        // Turn 45+R1 degrees clockwise
  chassis.wait_drive();
  chassis.set_drive_pid(132.4, DRIVE_SPEED, true);  // Move forward 132.4 inches
  chassis.wait_drive();
  chassis.set_turn_pid(-135, TURN_SPEED);           // Turn 135 degrees counterclockwise
  chassis.wait_drive();
  chassis.set_drive_pid(24, DRIVE_SPEED, true);  // Move backward AWP1 inches
  chassis.wait_drive();
  autonroller();
}


void autonskills1() {
  autonflywheel();
  autonroller();
  intakeon();
  // swing thing
  intakeoff();
  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-5, DRIVE_SPEED, true);
  chassis.wait_drive();
  autonroller();
  chassis.set_drive_pid(5, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(59, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(SK1, TURN_SPEED);
  chassis.wait_drive();
  // Index 3 discs pls
  chassis.set_turn_pid((90-SK1), TURN_SPEED);
  chassis.wait_drive();
  intakeon();
  chassis.set_drive_pid(117, DRIVE_SPEED, true);
  chassis.wait_drive();
  intakeoff();
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(23.4, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(SK2, TURN_SPEED);
  chassis.wait_drive();
  // Index 3 discs pls
  chassis.set_turn_pid((-SK2), TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(47, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-5, DRIVE_SPEED, true);
  chassis.wait_drive();
  autonroller();

}


void skillsauton(){
  autonflywheel(flywheel_start);
  chassis.set_drive_pid(-5, DRIVE_SPEED, true);
  autonroller();
  chassis.set_drive_pid(23.4, DRIVE_SPEED, true);
  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.set_drive_pid(46.8, DRIVE_SPEED, true);
  chassis.set_turn_pid(-90, TURN_SPEED);
  autonindex();
  intakeon();
  chassis.set_drive_pid(-5, DRIVE_SPEED, true);
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.set_drive_pid(46.8, 90, true);
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.set_drive_pid(5, DRIVE_SPEED, true);
  autonindex();
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.set_drive_pid(-27.4, DRIVE_SPEED, true);
  autonroller();




}
*/