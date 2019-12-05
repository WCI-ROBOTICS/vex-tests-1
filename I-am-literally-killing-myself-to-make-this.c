#pragma config(Motor,  port1,           motrev,        tmotorVex393_MC29, openLoop)
#pragma config(Sensor, dgtl1,  bmp,         sensorTouch)
// get ide here http://www.robotc.net/
task main(){
	int val = 0;
	int target = 0;
	int acc = 7;
	while(true)
	{
		if (SensorValue(bmp) == 1){
			 target = -127;
		}
		else{
			target = 127;
		}
		if (val < target){
			val = val+acc;
		}
		else{
			val = val-acc;
		}
		motor[motrev] = val;
		sleep(10);
	}
}
