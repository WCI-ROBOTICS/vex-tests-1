#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#pragma config(Motor,  port1,           motrev,        tmotorVex393_MC29, openLoop)
#pragma config(Sensor, dgtl1,  bmp,         sensorTouch)
// get ide here http://www.robotc.net/
// documentation: http://www.robotc.net/tutor/Cortex/cortexunits.php?platform=Cortex

int dt = 10;  // in miliseconds

// controls for pid loop
float Kp = .1;
float Ki = 0;
float Kd = .1;

float previous_error = 0;
float integral = 0;

void goToTarget(float target, short nam){
	float val = motor[nam];

    float error = target - val;
    integral = integral + error * dt; // dt might have to changed to seconds (divide by 1000)
    float derivative = (error - previous_error) / dt;
    float output = Kp * error + Ki * integral + Kd * derivative;
    previous_error = error;

    float next_vel = val + output;
    next_vel = MAX(-127, next_vel);
    next_vel = MIN(127, next_vel);
    motor[nam] = next_vel;
}

task main(){
	while (true){
		if (SensorValue(bmp) == 1){
			 goToTarget(-127, motrev);
		}
		else{
			goToTarget (127,motrev);
		}

		wait1Msec(dt);
	}
}