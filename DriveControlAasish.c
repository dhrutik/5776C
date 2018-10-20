#pragma config(Sensor, in3,    pot,            sensorPotentiometer)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define KP -0.01
#define KI 0.009

task straightPID() {
	int target = -400;
	int IntegralRaw = 0;
	int error = 0;
	int IntegralCap = 1200;
	float a;

	while(true) {
		if(vexRT[Btn7U]==1)
			stopTask(straightPID);
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
		if(SensorValue[pot] <= 30) {
			if(SensorValue[pot] >= 0) {
				motor[port4] = 0;
				return;
			}
		}
	}
}

task backwardPid() {
	int target = 3530;
	int IntegralRaw = 0;
	int error = 0;
	int IntegralCap = 1200;
	float a;

	while(true) {
		if(vexRT[Btn7U]==1) {
			stopTask(backwardPid);
		}
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
			if(SensorValue[pot] >= 3300) {
				motor[port4] = 0;
				return;
			}
		}
	}
}

task main()
{
	int doneValue = 1;
	bool done = false;
	while(true) {
		if(doneValue==-1) {
		motor[port8]=-(doneValue*vexRt[Ch2]);
		motor[port9] = doneValue*vexRt[Ch2];
		motor[port2] = -doneValue*vexRt[Ch3];
		motor[port3] = -doneValue*vexRt[Ch3];
	}
		else {
			motor[port8]=-(doneValue*vexRt[Ch3]);
			motor[port9] = doneValue*vexRt[Ch3];
			motor[port2] = -doneValue*vexRt[Ch2];
			motor[port3] = -doneValue*vexRt[Ch2];
		}

		if(vexRT[Btn5D] ==1)
			doneValue = 0-doneValue;
		motor[port6] = (vexRt[Btn6D]-0)*127-(vexRt[Btn6U]-0)*127;
		motor[port7] = vexRT[Btn8U]*127 - vexRT[Btn8D]*127;
		motor[port4] = vexRT[Btn7L]*30-vexRT[Btn7R]*30;
			//motor[port6] = (vexRT[Btn8L]-0)*127;
			//motor[port6] = (vexRT[Btn8R]-0)*-127;
			//motor[port4] = vexRT[Btn7L]*50-vexRT[btn7R]*50;

				/*if(vexRT[Btn7L]==1&&done=true) {
					if(taskStateRunning(straightPID)==true)
					motor[port4] = -25;
				}

				if(vexRT[Btn7R]==1) {
					motor[port4] = 25;
				}*/

				//if(SensorValue[pot]>2000 && vexRt[Btn5U]==1) {
					//startTask(straightPID);
				//}
				//else
					//if(vexRt[Btn5U]==1)
						//startTask(backwardPid);
			}

	}
