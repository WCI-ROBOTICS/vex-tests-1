#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#pragma config(Motor,  port1,           motrev,        tmotorVex393_MC29, openLoop)
#pragma config(Sensor, dgtl1,  bmp,         sensorTouch)
// get ide here http://www.robotc.net/
// documentation: http://www.robotc.net/tutor/Cortex/cortexunits.php?platform=Cortex

int dt = 10;  // in miliseconds

float start_vel = 0;
float prev_target = 0;

void goToTarget(float target, short nam){
	float vel = motor[nam];

    if (target != prev_target){
        start_vel = vel;
        prev_target = target;
    }

    float cMap = (vel-start_vel)/(target-start_vel);
    float acl = cMap*(1-cMap);
    if (~acl && target != vel){
        acl = .02;
    }
    float next_vel = vel + acl*( target-start_vel);

    next_vel = MAX(-127.0, next_vel);
    next_vel = MIN(127.0, next_vel);
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
