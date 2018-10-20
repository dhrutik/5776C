#pragma config(Sensor, in3,    pot,            sensorPotentiometer)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define KP -0.01
#define KI 0.009

static int straightPID() {
	int target = 370;
	int IntegralRaw = 0;
	int error = 0;
	int IntegralCap = 1200;
	float a;

	while(true) {
		error = target - SensorValue[pot];
		IntegralRaw += error;
		if(IntegralRaw > IntegralCap) {
			IntegralRaw = IntegralCap;
		}
		if(IntegralRaw < -1*IntegralCap) {
			IntegralRaw = -IntegralCap;
		}
		a = ((KP * error) - (KI * IntegralRaw));
		motor[port4] = -a;
		delay(25);
		if(SensorValue[pot] <= 630) {
			if(SensorValue[pot] >= 320) {
				motor[port4] = 0;
				return 0;
			}
		}
	}
}

static int backwardPid() {
	int target = 3530;
	int IntegralRaw = 0;
	int error = 0;
	int IntegralCap = 1200;
	float a;

	while(true) {
		error = target - SensorValue[pot];
		IntegralRaw += error;
		if(IntegralRaw > IntegralCap) {
			IntegralRaw = IntegralCap;
		}
		if(IntegralRaw < -1*IntegralCap) {
			IntegralRaw = -IntegralCap;
		}
		a = ((KP * error) - (KI * IntegralRaw));
		motor[port4] = -a;
		delay(25);
		if(SensorValue[pot] <= 3580) {
			if(SensorValue[pot] >= 3480) {
				motor[port4] = 0;
				return 0;
			}
		}
	}
}


task main()
{
	int doneValue = 1;
	bool done = false;
	while(true) {
		motor[port8]=-(doneValue*vexRt[Ch2]);
		motor[port9] = doneValue*vexRt[Ch2];
		motor[port2] = doneValue*vexRt[Ch3];
		motor[port3] = doneValue*vexRt[Ch3];
			if(vexRT[Btn5D] ==1)
				doneValue = 0-doneValue;
			motor[port6] = (vexRt[Btn6D]-0)*127;
			motor[port7] = (vexRt[Btn6D]-0)*127;
			motor[port6] = -(vexRt[Btn6U]-0)*127;
			motor[port7] = -(vexRt[Btn6U]-0)*127;
			motor[port5] = (vexRT[Btn8U]-0)*127;
			motor[port5] = -((vexRT[Btn8D]-0)*127);
			if(SensorValue[pot]>2000 && vexRt[btn5u]==1) {
				straightPID();
			}
			else
				if(vexRt[Btn5U]==1)
					backwardPid();
	}
}