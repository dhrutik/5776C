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
 int rpm = 200;
 bool p = false;
 int rot; //interchangeable rpm
 pros::Controller master(pros::E_CONTROLLER_MASTER);
 pros::Motor mtr1(1, true);
 pros::Motor mtr2(2, true);
 pros::Motor mtr3(3);
 pros::Motor mtr4(4);
 pros::Motor fly1(5);
 pros::Motor fly2(9);
 pros::Motor intake(7);
 pros::Motor indexer(8);
 pros::Vision vision_sensor(9);
 pros::ADIDigitalIn limit (1);
float kp = 0.6, ki = 0.07, scale = 120;
float integral_raw = 0;
float integral, proportion, error, error2, error3, pwr;


void PID(int rpm){
    
    
    error = rpm - abs(fly1.get_actual_velocity());
    error2 = rpm - abs(fly2.get_actual_velocity());
    error3 = (error + error2)/2;
    proportion = error3 * kp;
    if(integral_raw < 1000) {integral_raw += error3;}
    integral = integral_raw * ki;
    pwr = scale * (integral + proportion);
    fly1.move_voltage(pwr);
    fly2.move_voltage(pwr*-1);
      
}
 void power_down_flywheel(void* param) {
   while(true) {
    fly1.move(0);
    fly2.move(0);
    pros::delay(10);
   }
 }

 void power_up_flywheel(void* param) {
  

   while(true) {
     PID(rot);
     pros::delay(20);
   }
 }


 void drive(int l, int r) {
   mtr3.move(l);
   mtr4.move(l);
   mtr1.move(r);
   mtr2.move(r);
 }

 void config_color
 (pros::vision_signature &color,
  uint8_t id,
  int32_t u_min,
  int32_t u_max,
  int32_t u_mean,
  int32_t v_min,
  int32_t v_max,
  int32_t v_mean,
  float range,
  uint32_t type,
  uint32_t rgb) {
    color.id = id;
    color.range = range;
    color.u_min = u_min;
    color.u_max = u_max;
    color.u_mean = u_mean;
    color.v_min = v_min;
    color.v_max = v_max;
    color.v_mean = v_mean;
    color.rgb = rgb;
    color.type = type;
  }
/*
 void sensor() {
  float kp = -0.75;
  int power = 0;
  float error;
  float flag_y;
  pros::vision_signature_s_t CLR;
  config_color(CLR, 1, 389, 1555, 972, -4859, -4025, -4442, 2.8, 0, 0);
  vision_sensor.set_signature(1, &CLR);
  while(true) {
    pros::vision_object_s_t flag = vision_sensor.get_by_sig(0, 1);
    pros::delay(25);
    if(flag.signature == 255) break;
    error = 100 - flag.y_middle_coord;
    power = (error * kp);
    intake.move(power);
    if(master.get_digital(DIGITAL_Y) == true) break;
    pros::delay(25);
  }
}
*/

 pros::Task pwrup (power_up_flywheel, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "up");
 pros::Task pwrdwn (power_down_flywheel, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "down");

 void DriveControl() {
   float scale = 1;
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
     
     mtr3.move(master.get_analog(ANALOG_LEFT_Y) * scale);
     mtr4.move(master.get_analog(ANALOG_LEFT_Y) * scale);
     mtr1.move(master.get_analog(ANALOG_RIGHT_Y) * scale);
     mtr2.move(master.get_analog(ANALOG_RIGHT_Y) * scale);
     if(master.get_digital(DIGITAL_LEFT)){
       pwrup.resume();
       rot = 200;
       pwrdwn.suspend();
     }
     if(master.get_digital(DIGITAL_RIGHT)){
       pwrup.resume();
       rot = 75;
       pwrdwn.suspend();

     }
     if(master.get_digital(DIGITAL_L2)){
       intake.move(200);
     }
     else{
       intake.move(-200);
     }
     if(master.get_digital(DIGITAL_Y)){
       pwrup.resume();
       rot = 120;
       pwrdwn.suspend();
     }

     if(master.get_digital(DIGITAL_A)){
       pwrup.resume();
       rot = 80;
       pwrdwn.suspend();
     }
     

     
     if(master.get_digital(DIGITAL_R1) == true) {
       indexer.move_velocity(-200);
     }
     else if(master.get_digital(DIGITAL_R2) == true) {
       indexer.move_velocity(200);
     }
     else {
       indexer.move(0);
     }
     //if(master.get_digital(DIGITAL_X) == true) {
       //pwrup.resume();
       //pwrdwn.suspend();
     //}
     if(master.get_digital(DIGITAL_B) == true) {
       pwrup.suspend();
       pwrdwn.resume();
     }
     pros::delay(25);
   }
 }



void opcontrol() {
  
  DriveControl();



	}
