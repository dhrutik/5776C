#include "main.h"
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

 pros::Controller master(pros::E_CONTROLLER_MASTER);
 pros::Motor mtr1(1, true);
 pros::Motor mtr2(2, true);
 pros::Motor mtr3(3);
 pros::Motor mtr4(4);
 pros::Motor fly1(5);
 pros::Motor fly2(6);
 pros::Motor intake(7);
 pros::Motor flipper(8);
 pros::Motor set_encoder_units(MOTOR_ENCODER_COUNTS);

 bool power_up = true;
 bool powered_down = false;
 bool powered_up = false;

 void movebase(int l, int r) {
  mtr3.move(l);
  mtr4.move(l);
  mtr1.move(r);
  mtr2.move(r);
 }

 void moveticks(int l, int vl, int r, int vr) {
  mtr3.move_relative(l, vl);
  mtr4.move_relative(l, vl);
  mtr1.move_relative(r, vr);
  mtr2.move_relative(r, vr);
 }

 void power_down_flywheel(void* param) {
   while(true) {
     if(powered_up == true) {
       for(int c = 3; c <= 1; c++) {
         fly1.move(-40 * c);
         fly2.move(40 * c);
         pros::delay(1000);
       }
       fly1.move(0);
       fly2.move(0);
       powered_down = true;
       powered_up = false;
    }
    else {
      fly1.move(0);
      fly2.move(0);
      intake.move(0);
      powered_down = true;
      powered_up = false;
    }
     pros::delay(10);
   }
 }

 void power_up_flywheel(void* param) {
   while(true) {
     fly1.move_velocity(200);
     fly2.move_velocity(-200);
     pros::delay(20);
   }
 }

void opcontrol() {
  fly1.set_gearing(pros::E_MOTOR_GEARSET_18);
  fly2.set_gearing(pros::E_MOTOR_GEARSET_18);
  pros::Task pwrup (power_up_flywheel, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "up");
  pros::Task pwrdwn (power_down_flywheel, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "down");
  pwrup.suspend();
  pwrdwn.suspend();

  mtr1.tare_position();
  mtr3.tare_position();
  pwrup.suspend();
  pwrdwn.suspend();
  while(true) {
    mtr3.move(master.get_analog(ANALOG_LEFT_Y));
    mtr4.move(master.get_analog(ANALOG_LEFT_Y));
    mtr1.move(master.get_analog(ANALOG_RIGHT_Y));
    mtr2.move(master.get_analog(ANALOG_RIGHT_Y));
    if(master.get_digital(DIGITAL_L1) == true) {
      intake.move_velocity(-200);
    }
    if(master.get_digital(DIGITAL_L2) == true) {
      intake.move_velocity(200);
    }
    flipper.move((master.get_digital(DIGITAL_R1) - master.get_digital(DIGITAL_R2)) * 127);
    if(master.get_digital(DIGITAL_X)) {
      pwrup.resume();
      pwrdwn.suspend();
    }
    if(master.get_digital(DIGITAL_B)) {
      pwrup.suspend();
      pwrdwn.resume();
    }
    pros::delay(25);
  }

}
