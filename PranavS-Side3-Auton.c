#pragma config(Sensor, in3,    pot,     sensorPotentiometer)
#pragma config(Sensor, dgtl7,  driveEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  liftEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port2,           rightFront,    tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port3,           rightBack,     tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port5,           puncherMotor,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           liftRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           liftLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           leftFront,     tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port9,           leftBack,      tmotorVex393_MC29, openLoop, driveLeft)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int lift_target = 300;
#define KP -0.2
#define KI 0.006
static int straightPID(int target) {
	//int target = 460;
	int IntegralRaw = 0;
	int error = 0;
	int IntegralCap = 1200;
	SensorValue[driveEncoder] = 0;
	float a;

	while(true) {
		error = target - SensorValue[driveEncoder];
		IntegralRaw += error;
		if(IntegralRaw > IntegralCap) {
			IntegralRaw = IntegralCap;
		}
		if(IntegralRaw < -1*IntegralCap) {
			IntegralRaw = -IntegralCap;
		}
		a = ((KP * error) - (KI * IntegralRaw));
		motor[port2] = -a/2;
		motor[port3] = -a/2;
		motor[port8] = -a/2;
		motor[port9] = -a/2;
		delay(25);
		if(SensorValue[driveEncoder] <= 465) {
			if(SensorValue[driveEncoder] >= 455) {
				motor[port2] = 0;
				motor[port3] = 0;
				motor[port8] = 0;
				motor[rightBack] = 0;
				return 0;
			}
		}
	}
}
//static int PID90(int turn_target) {
//	//int turn_target = 460;
//	int IntegralRaw = 0;
//	int error = 0;
//	int IntegralCap = 1200;
//	SensorValue[driveEncoder] = 0;
//	float a;

//	while(true) {
//		error = turn_target- SensorValue[driveEncoder];
//		IntegralRaw += error;
//		if(IntegralRaw > IntegralCap) {
//			IntegralRaw = IntegralCap;
//		}
//		if(IntegralRaw < -1*IntegralCap) {
//			IntegralRaw = -IntegralCap;
//		}
//		a = ((KP * error) - (KI * IntegralRaw));
//		motor[port8] = -a;
//		motor[port2] = a;
//		motor[port9] = a;
//		delay(25);
//		if(SensorValue[driveEncoder] <= 465) {
//			if(SensorValue[driveEncoder] >= 455) {
//				motor[port8] = 0;
//				motor[port2] = 0;
//				motor[port9] = 0;
//				return 0;
//			}
//		}
//	}
//}

//PID for Lift

//task downLiftPID()
//{
//	int target = lift_target*-1;
//	int error = 999;
//	float integralraw = 0;
//	float proportion = 0;
//	float kp = 0.65;
//	float integral = 0;
//	float ki = 0.02;
//	SensorValue[liftEncoder] = 0;
//	while(true) {
//		error = target - SensorValue[liftEncoder];
//		proportion = kp * error;
//		ki = error / target;
//		integralraw += error;
//		integral = integralraw * ki;
//		motor[liftRight] = (int)(proportion + integral);
//		motor[liftLeft] = (int)(proportion + integral);
//		delay(50);
//	}
//}

//task LiftPID()
//{
//	int error = 999;
//	float integralraw = 0;
//	float proportion = 0;
//	float kp = 0.65;
//	float integral = 0;
//	float ki = 0.02;
//	SensorValue[liftEncoder] = 0;
//	while(true) {
//		error = lift_target - SensorValue[liftEncoder];
//		proportion = kp * error;
//		ki = error / lift_target;
//		integralraw += error;
//		integral = integralraw * ki;
//		motor[liftRight] = (int)(proportion + integral);
//		motor[liftLeft] = (int)(proportion + integral);
//		delay(50);
//	}
//}

void puncherAuton(){
	motor[port7] = 127;
	wait1Msec(5000);
	motor[port7] = 0;


}

task main()
{
		puncherAuton();
		straightPID(100);
		straightPID(-100);






}
