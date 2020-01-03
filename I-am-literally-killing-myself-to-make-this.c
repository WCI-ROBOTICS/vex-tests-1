#pragma config(Motor,  port1,           motrev,        tmotorVex393_MC29, openLoop)
#pragma config(Sensor, dgtl1,  bmp,         sensorTouch)
// get ide here http://www.robotc.net/
// documentation: http://www.robotc.net/tutor/Cortex/cortexunits.php?platform=Cortex

int Dt = 10;

int Kp = .1;
int Ki = 0;
int Kd = .1;

int previous_error = 0;
int integral = 0;

void goToTarget(float target, short nam){
	int val = motor[nam];

    error = target - val;
    integral = integral + error * dt; // dt might have to changed to miliseconds (devide by 1000)
    derivative = (error - previous_error) / dt;
    output = Kp * error + Ki * integral + Kd * derivative;
    previous_error = error;

    motor[nam] = val + output;
}

task main(){
	while (true){
		if (SensorValue(bmp) == 1){
			 goToTarget(-127, motrev);
		}
		else{
			goToTarget (127,motrev);
		}

		wait1Msec(Dt);
	}
}