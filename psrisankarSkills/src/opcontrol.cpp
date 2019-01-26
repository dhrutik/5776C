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
float kp = 0.6, ki = 0.06, scale = 120;
float integral_raw = 0;
float integral, proportion, error, pwr;


void PID(int rpm){
    
    
    error = rpm - abs(m.get_actual_velocity());
    proportion = error * kp;
    if(integral_raw < 1000) {integral_raw += error;}
    integral = integral_raw * ki;
    pwr = scale * (integral + proportion);
    m.move_voltage(pwr);
    m2.move_voltage(pwr*-1);
      
}
void opcontrol() {
    while (true){
        if (master.get_digital(DIGITAL_A)) {
            rollers.move(-200);
    }
        else {
            rollers.move(0);
    }
        if (master.get_digital(DIGITAL_B)) {
            indexer.move(-200);
    }
        else {
            indexer.move(0);
    }
        PID(90);
    }
} 
