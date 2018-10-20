int lift_target = 414;

task LiftPID()
{
	int error = 999;
	float integralraw = 0;
	float proportion = 0;
	float kp = 0.65;
	float integral = 0;
	float ki = 0.02;
	SensorValue[lift] = 0;
	while(true) {
		error = lift_target - SensorValue[dgtl6];
		proportion = kp * error;
		ki = error / lift_target;
		integralraw += error;
		integral = integralraw * ki;
		motor[port6] = (int)(proportion + integral);
		if(vexRT[Btn6U] == 1 || vexRT[Btn6D] == 1)
			break;
		delay(50);
	}
}
