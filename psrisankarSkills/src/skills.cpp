void skills() {
   rpm = 120;
   pwrup.suspend();
   pwrdwn.suspend();
   pros::delay(25);

   pwrup.resume();
   moveticks(2800, 150, 2800, 150);
   intake.move(-50);
   pros::delay(2000);
   movebase(0,0);
   pros::delay(500);
   intake.move(-127);
   pros::delay(500);

   indexer.move(-100);
   pros::delay(600);
   movebase(100,100);
   intake.move(90);
   indexer.move(0);
   pros::delay(300);
   movebase(0,0);
   pros::delay(500);
   movebase(-100, -100);
   pros::delay(300);

   intake.move(0);
   moveticks(-3300, -150, -3300, -150); //Double check these values, they may be off
   pros::delay(2000);

   moveticks(970, 100, -970, -100);
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
   intake.move(-50);
   pros::delay(1500);
   intake.move(0);

   indexer.move(-100);
   pros::delay(1000);
   indexer.move(0);

   pwrup.suspend();
   pwrdwn.resume();

   moveticks(1500, 150, 1500, 150);
   pros::delay(1500);

   moveticks(-1500, -150, -1500, -140);
   pros::delay(1400);

   moveticks(-900, -100, 900, 100);
   pros::delay(1300);

   movebase(100, 100);
   intake.move(127);
   pros::delay(500);
   movebase(0,0);
   intake.move(0);

   moveticks(-1000,-150,-1000,-150);
   pros::delay(900);

   movebase(100,100);
   pros::delay(200);

   moveticks(-900,-150,900,150);
   pros::delay(900);

   moveticks(3500,150,3500,150);
   pros::delay(2000);

   moveticks(900,150,-900,-150);
   pros::delay(900);
 }
