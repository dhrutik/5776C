#pragma config(Sensor, in2,    pot,            sensorPotentiometer)
#pragma config(Sensor, dgtl4,  drive,          sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  flywheel,       sensorQuadEncoder)
#pragma config(Motor,  port2,           RF,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           RB,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           LD,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,           ,             tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma debuggerWindows (debugStream)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
MOTOR PORTS [ 2 - 5 ] : DRIVE
MOTOR PORTS [ 6 ] : LIFT
MOTOR PORTS [ 7 ] : CAP-FLIPPER
MOTOR PORTS [ 8 ] : FLYWHEEL
MOTOR PORTS [ 9 ] : BALL-INTAKE
*/

static void movebase(int l, int r)
{
	motor[port2] = r; //Right
	motor[port3] = r; //Right
	motor[port4] = l; //Left
	motor[port5] = l; //Left
}

static void PID(int ticks)
{
	int error = 0;
	int power = 0;
	float proportion = 0;
	float integral = 0;
	float integralraw = 0;
	float kp = 0.09;
	float ki = 0.006;
	SensorValue[drive] = 0;
	while(true)
	{
		error = ticks - SensorValue[drive];
		proportion = kp * error;
		integralraw += error;
		integral = integralraw * ki;
		power = (int)(proportion - integral);
		motor[LD] = power;
		motor[RB] = power;
		motor[RF] = power;
		delay(25);
		writeDebugStream("Sensor: %d", SensorValue[drive]);
		writeDebugStream(" Error: %d", error);
		writeDebugStream(" Proportion: %d", proportion);
		writeDebugStream(" Integral: %d", integral);
		writeDebugStream(" Power: %d", power);
		delay(25);
		writeDebugStreamLine("");
	}
	motor[port7] = 0;
	motor[port8] = 0;
	motor[port9] = 0;
}

static void FlyWheelPID(int v)
{
	int error = 0;
	int prev_error = 0;
	float kd = 0.3;
	float derivative = 0;
	int power = 0;
	bool quit = false;
	for(int x = 0; x < 9; x++) {
		power += 10;
		motor[port7] = power;
		motor[port8] = power;
		wait(1);
	}
	SensorValue[flywheel] = 0;
	v = 360 * (v / 60);
	clearTimer(T1);
	power = 100;
	while(time1[T1] <= 10000)
	{
		error = v - SensorValue[flywheel];
		derivative = (error - prev_error) * kd;
		motor[port7] = power + derivative;
		motor[port8] = power + derivative;
		prev_error = error;
		writeDebugStreamLine("Error: %d Sensor: %d", derivative, SensorValue[flywheel]);
		wait(1);
		SensorValue[flywheel] = 0;
	}
	power = derivative;
	for(int x = 0; x < power/10; x++) {
		power -= 10;
		motor[port7] = power;
		motor[port8] = power;
		wait(1);
	}
	motor[port7] = 0;
	motor[port8] = 0;
}

task main()
{
	motor[port7] = 100;
	motor[port8] = 100;
	wait(5);
}