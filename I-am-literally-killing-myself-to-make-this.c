#pragma config(Motor,  port1,           motrev,        tmotorVex393_MC29, openLoop)
#pragma config(Sensor, dgtl1,  bmp,         sensorTouch)
// get ide here http://www.robotc.net/
// documentation: http://www.robotc.net/tutor/Cortex/cortexunits.php?platform=Cortex
void goToTarget(float target, short nam){
	int acc = 7;
	int val = motor[nam];

	while (abs(val - target) < acc){
			acc = acc/2;
			if (acc<=1) break;
	}

	if (val == target){
		val=val;
	}
	else if (val < target){
		val = val+acc;
	}
	else{
		val = val-acc;
	}
	motor[nam] = val;
}

task main(){
	while (true){
		if (SensorValue(bmp) == 1){
			 goToTarget(-127, motrev);
		}
		else{
			goToTarget (127,motrev);
		}

		wait1Msec(10);
	}
}
