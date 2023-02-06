#include "main.h"
#include "pros/misc.h"
#include "globals.hpp"

//test comment

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////

int tune_turn;
// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(0, 0);
  chassis.set_slew_distance(0, 0);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}


void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

//FLYWHEEL CONSTANTS-------------------------------------
const int DRIVE_SPEED = 100; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;

int flywheel_start = 3600;

int TUNE = 550;

int L1 = 30;
int L2 = 10;

int SK1 = 20;
int SK2 = 20;
int currentSpeed = 0;
int error= 0;
float Kp = 0;
float Ki = 0;
float Kd = 0;
double targetSpeed = 0;
//FLYWHEEL CONSTANTS--------------------------------------
void wait(int waitTime) {
    int t = 0;
    while (t < waitTime) {
        t += 2;
        flywheel::voltageUpdate();
        pros::delay(20);
    };
};


void intakeon() {
  intake::spin(-12000);
};

void outtakeon() {
  intake::spin(12000);
  pros::delay(2000);
}

void intakeoff() {
  intake::spin(0);
};

void autonroller() {
  intake::spin(-400);
  pros::delay(375);
  intake::spin(0);
};





// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  {-3,-5,-18},

  // Right Chassis Ports (negative port will reverse it!)
  {16, 8, 14}

  // IMU Port
  ,21

  // Tracking Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  ,4.125

  // Ticks per Rotation of Encoder
  ,600

  // External Gear Ratio of Tracking Wheel (MUST BE DECIMAL)
  // eg. if your drive is 84:36 where the 36t is sensored, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is sensored, your RATIO would be 0.6.
  ,2.333

);


void initialize() {
  // Print our branding over your terminal :D
  pros::lcd::initialize();
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  expansion1.set_value(false);
  odometry::odometryController();
  

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0.2); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0.1, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!
  exit_condition_defaults(); // Set the exit conditions to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  /*ez::as::auton_selector.add_autons(
    {
      Auton("asdfas", autonleft),
    }
  );
  */

 
  
}




void disabled() {
}



void competition_initialize() {
  expansion1.set_value(false);
  
}



void autonomous() {
  /*
  //right auton 2
  flywheel.move_velocity(600); // flywheel on
  intakeon();
  chassis.set_drive_pid(25, DRIVE_SPEED, true, true);// forward 25 in
  chassis.wait_drive();
  chassis.set_turn_pid(30, TURN_SPEED); // turn 35 deg
  chassis.wait_drive();
  intakeoff();
  pros::delay(3000); //wait 3 seconds
  pros::delay(1000); //wait 1 seconds
  outtakeon();
  pros::delay(3000);
  intakeoff();
  chassis.set_drive_pid(-25, DRIVE_SPEED, true, true);
  chassis.wait_drive();
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-10, DRIVE_SPEED, true, true);
  chassis.wait_drive();
  autonroller();
  chassis.wait_drive();
  //*/
  
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
   // Set motors to hold.  This helps autonomous consistency.
  chassis.set_angle(0);
  chassis.set_max_speed(125);

  targetSpeed = 600;
  chassis.wait_drive();
  chassis.set_drive_pid(36.7, DRIVE_SPEED, false, true);
  chassis.wait_drive();
  chassis.set_turn_pid(40, TURN_SPEED);
  chassis.wait_drive();
  targetSpeed = 600;
  pros::delay(4000);
  outtakeon();
  pros::delay(2000);
  chassis.wait_drive();
  targetSpeed = 0;
  chassis.set_drive_pid(-5, DRIVE_SPEED, false, true);
  chassis.wait_drive();
  intakeoff();
  chassis.set_turn_pid(-30, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-50, DRIVE_SPEED, false, true);
  chassis.wait_drive();
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-10, DRIVE_SPEED, false, true);
  chassis.wait_drive();
  autonroller();
  



  /*
  flywheel.move_velocity(550);
  chassis.set_drive_pid(-7, DRIVE_SPEED);
  chassis.wait_drive();
  autonroller();
  
  intakeon();
  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(45, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-(45-L1), TURN_SPEED);
  flywheel.move_velocity(-510);
  chassis.wait_drive();

  outtakeon();
  pros::delay(3000);
  intakeoff();

  chassis.set_drive_pid(15, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-85, DRIVE_SPEED);
  chassis.wait_drive();
  pros::delay(500);
  chassis.set_drive_pid(13, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-30, DRIVE_SPEED);
  chassis.wait_drive();
  autonroller();
  //*/
  
  
  //Right Roller Auton
  /*
  flywheel.move_velocity(600);
  chassis.set_drive_pid(-23.4, DRIVE_SPEED, true);  // Move 23.4 inches backward
  chassis.wait_drive(); 
  chassis.set_turn_pid(90, TURN_SPEED);             // Turn 90 degrees clockwise
  chassis.wait_drive();
  chassis.set_drive_pid(-6, DRIVE_SPEED, true);     // Move 5 inches backward
  chassis.wait_drive();
  autonroller();                                    // Claim Roller
  chassis.wait_drive();
  chassis.set_drive_pid(10, DRIVE_SPEED, true);     // Move 10 inches forward
  chassis.wait_drive();
  
  outtakeon();
  pros::delay(3000);
  intakeoff();
  //*/

}



void opcontrol() {
  
  
  expansion1.set_value(false);
  
  flywheel::setTargetSpeed(0);
  
  int intake_mode = 0; // Sets up intake control for buttons
  int flywheel_mode = 0; //Sets up flywheel control for buttons
  while (true) { 
    odometry::update();
   //DRIVE
    chassis.tank(); 
    
    pros::delay(20);
    //INTAKE
    
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))intake::spin(1); // When R1 pressed,
    else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))intake::spin(-1);
    else intake::spin(0);
    
    //EXPANSION
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y))expansion1.set_value(true);
  
    // FLYWHEEL
    if ((master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)))  { // When L1 pressed,
        flywheel::setTargetSpeed(LONG_RANGE_POWER);
        wait(3000);
        
    }
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))    { // When L2 pressed,
      flywheel::setTargetSpeed(SHORT_RANGE_POWER);
      wait(3000);
    }
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))    { // When B pressed,
      flywheel::setTargetSpeed(1);
      wait(3000);
    }

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
    
  }

}
