#include "api.h"
#include "main.h"
#pragma once
extern int rpm;
extern int rot;
extern int roll;
extern pros::Controller master;
extern pros::Motor mtr1;
extern pros::Motor mtr2;
extern pros::Motor mtr3;
extern pros::Motor mtr4;
extern pros::Motor fly1;
extern pros::Motor fly2;
extern pros::Motor roller;
extern pros::Motor indexer;
extern pros::Vision vision_sensor;
extern pros::ADIDigitalIn limit;
void power_down_flywheel();
void power_up_flywheel();
void sensor();
extern pros::Task pwrup;
extern pros::Task pwrdwn;
extern pros::Task roller_in;
extern pros::Task roller_out;