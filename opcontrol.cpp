#include "main.h"
#define R 1
#define B 2
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
 int rpm = 150;
 bool p = false;
 pros::Controller master(pros::E_CONTROLLER_MASTER);
 pros::Motor mtr1(1, true);
 pros::Motor mtr2(2, true);
 pros::Motor mtr3(3);
 pros::Motor mtr4(4);
 pros::Motor fly1(5);
 pros::Motor fly2(9);
 pros::Motor intake(7);
 pros::Motor flipper(8);
 pros::Vision vision_sensor(9);

 void power_down_flywheel(void* param) {
   while(true) {
    fly1.move(0);
    fly2.move(0);
    pros::delay(10);
   }
 }

 void power_up_flywheel(void* param) {
   while(true) {
     fly1.move_velocity(rpm);
     fly2.move_velocity(-rpm);
     pros::delay(20);
   }
 }

 void drive(int l, int r) {
   mtr3.move(l);
   mtr4.move(l);
   mtr1.move(r);
   mtr2.move(r);
 }
 
 pros::Task pwrup (power_up_flywheel, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "up");
 pros::Task pwrdwn (power_down_flywheel, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "down");

 void DriveControl() {
   fly1.move(0);
   fly2.move(0);
   fly1.set_gearing(pros::E_MOTOR_GEARSET_18);
   fly2.set_gearing(pros::E_MOTOR_GEARSET_18);
   pwrup.suspend();
   pwrdwn.suspend();
   mtr1.tare_position();
   mtr3.tare_position();
   pwrup.suspend();
   pwrdwn.suspend();
   fly1.move(0);
   fly2.move(0);
   while(true) {
     mtr3.move(master.get_analog(ANALOG_LEFT_Y));
     mtr4.move(master.get_analog(ANALOG_LEFT_Y));
     mtr1.move(master.get_analog(ANALOG_RIGHT_Y));
     mtr2.move(master.get_analog(ANALOG_RIGHT_Y));
     if(master.get_digital(DIGITAL_L1) == true) {
       intake.move_velocity(-200);
     }
     else if(master.get_digital(DIGITAL_L2) == true) {
       intake.move_velocity(200);
     }
     else {
       intake.move_velocity(0);
     }
     flipper.move((master.get_digital(DIGITAL_R1) - master.get_digital(DIGITAL_R2)) * 127);
     if(master.get_digital(DIGITAL_X) == true) {
       pwrup.resume();
       pwrdwn.suspend();
     }
     if(master.get_digital(DIGITAL_B) == true) {
       pwrup.suspend();
       pwrdwn.resume();
     }
     if(master.get_digital(DIGITAL_Y) == true) {
       sensor();
     }
     pros::delay(25);
   }
 }

void opcontrol() {
  rpm = 200;
  autonomous();
  rpm = 150;
  DriveControl();
}
