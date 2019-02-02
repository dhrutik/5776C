#include "main.h"
#include "init.h"
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
 int rb = 1; // 1 for blue; -1 for red

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

 void SixPointAuton() {
   pwrup.suspend();
   pwrdwn.suspend();
   pros::delay(25);

   pwrup.resume();
   pros::delay(2500);
   roller.move_velocity(-200);
   pros::delay(1000);
   roller.move(0);
   pros::delay(1);

   moveticks(-880 * rb, -100 * rb, 880 * rb, 100 * rb);
   pros::delay(1500);

   moveticks(3000, 150, 3000, 150);
   roller.move(-50);
   pros::delay(2000);

   indexer.move_velocity(-170);
   pros::delay(500);
   indexer.move_velocity(0);
   pros::delay(1);

   moveticks(-2900, -150, -2900, -150);
   pros::delay(1600);

   moveticks(880 * rb, 100 * rb, -880 * rb, -100 * rb);
   pros::delay(1300);

   moveticks(1700, 150, 1700, 150);
   pros::delay(1600);

   indexer.move_velocity(-200);
   pros::delay(1000);
   indexer.move(0);
 }

 void SevenPointAuton() {
   rpm = 120;
   pwrup.suspend();
   pwrdwn.suspend();
   pros::delay(25);

   pwrup.resume();
   moveticks(2800, 150, 2800, 150);
   roller.move(-50);
   pros::delay(2000);
   movebase(0,0);
   pros::delay(500);
   roller.move(-127);
   pros::delay(500);

   roller.move(0);
   moveticks(-2900, -150, -2900, -150);
   pros::delay(1500);

   moveticks(920 * rb, 100 * rb, -920 * rb, -100 * rb);
   pros::delay(1400);

   movebase(50,50);
   pros::delay(200);
   movebase(0,0);
   pros::delay(100);

   indexer.move(-100);
   pros::delay(500);
   indexer.move(0);
   pros::delay(100);

   moveticks(1500, 150, 1500, 140);
   roller.move(-50);
   pros::delay(1500);
   roller.move(0);

   indexer.move(-100);
   pros::delay(1000);
   indexer.move(0);

   pwrup.suspend();
   pwrdwn.resume();

   moveticks(1500, 150, 1500, 150);
   pros::delay(1500);

   moveticks(-1500, -150, -1500, -140);
   pros::delay(1400);

   moveticks(-900 * rb, -100 * rb, 900 * rb, 100 * rb);
   pros::delay(1300);

   movebase(100, 100);
   roller.move(127);
   pros::delay(500);
   movebase(0,0);
   roller.move(0);
 }

 void BackAuton() {
   rpm = 90;
   pwrup.suspend();
   pwrdwn.suspend();
   fly1.move_velocity(0);
   fly2.move_velocity(0);
   moveticks(2800,150,2800,150);
   roller.move(-50);
   pros::delay(2000);
   movebase(0,0);
   pros::delay(500);
   roller.move(-127);
   pros::delay(500);
   roller.move(0);
   moveticks(-2000,-150,-2000,-150);
   pros::delay(800);
   indexer.move(0);
   moveticks(-525 * rb, -150 * rb, 525 * rb, 150 * rb);
   pros::delay(1000);
   indexer.move(-50);
   roller.move(-100);
   pros::delay(600);
   indexer.move(0);
   moveticks(2000,100,2000,100);
   roller.move(120);
   pros::delay(1000);
   indexer.move(-100);
   pros::delay(300);
   indexer.move(0);
   moveticks(500,75,500,75);
   roller.move(120);
   pros::delay(500);
   roller.move(0);
   moveticks(-980, -100, -980, -100);
   pros::delay(1000);
   indexer.move(50);
   pros::delay(300);
   indexer.move(0);
   pwrup.resume();
   moveticks(450*rb, 150*rb, -450*rb, -150*rb);
   pros::delay(500);
   moveticks(680*rb, 150*rb, -680*rb, -150*rb);
   pros::delay(1100);
   moveticks(4000,200,4000,200);
   pros::delay(2500);
   moveticks(-100 * rb, -50 * rb, 100 * rb, 50 * rb);
   pros::delay(200);
   movebase(0,0);
   pros::delay(500);
   indexer.move(-100);
   pros::delay(200);
   indexer.move(0);
 }

 void skills() {
   rpm = 120;
   pwrup.suspend();
   pwrdwn.suspend();
   pros::delay(25);

   pwrup.resume();
   moveticks(2800, 150, 2800, 150);
   roller.move(-50);
   pros::delay(2000);
   movebase(0,0);
   pros::delay(500);
   roller.move(-127);
   pros::delay(500);

   indexer.move(-85);
   roller.move(-100);
   pros::delay(300);
   indexer.move(0);
   roller.move(0);

   moveticks(900,100,900,100);
   roller.move(100);
   pros::delay(500);
   roller.move(0);
   movebase(0,0);
   pros::delay(500);
   roller.move(0);
   moveticks(-3300, -150, -3300, -150);
   pros::delay(1500);

   moveticks(920, 100, -920, -100);
   pros::delay(1400);

   movebase(50,50);
   pros::delay(200);
   movebase(0,0);
   pros::delay(100);

   indexer.move(-100);
   pros::delay(500);
   indexer.move(0);
   pros::delay(100);

   moveticks(1500, 150, 1500, 140);
   roller.move(-50);
   pros::delay(1500);
   roller.move(0);

   indexer.move(-100);
   pros::delay(1000);
   indexer.move(0);

   pwrup.suspend();
   pwrdwn.resume();

   moveticks(1500, 150, 1500, 140);
   pros::delay(1500);

   moveticks(-1500, -150, -1500, -140);
   pros::delay(1400);

   moveticks(-900, -100, 900, 100);
   pros::delay(1300);

   movebase(100, 100);
   roller.move(127);
   pros::delay(700);
   movebase(0,0);
   roller.move(0);

   movebase(-100,-100);
   pros::delay(700);

   movebase(100,100);
   pros::delay(400);

   moveticks(-900, 100, 900, 100);
   pros::delay(900);

   moveticks(1500,150,1500,150);
   pros::delay(1000);
 }

void autonomous() {
  SevenPointAuton();
}
