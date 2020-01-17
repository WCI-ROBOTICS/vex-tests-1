#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393,           openLoop, reversed)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex393,           openLoop, reversed)
// get ide here http://www.robotc.net/
// documentation: http://www.robotc.net/tutor/Cortex/cortexunits.php?platform=Cortex

int dt = 10;  // in miliseconds


bool inDeadZone(float value1, float value2, float deadZone){
	if (abs(value1 - value2) < deadZone){
		return true;
	}
	return false;
}

void goToTarget(float target, short nam, float *start_vel, float *prev_target){
	float vel = motor[nam];

	if (~inDeadZone(target, *prev_target, .5)){
		*start_vel = vel;
		*prev_target = target;
	}

	float cMap = (vel-*start_vel)/(target-*start_vel);
	float acl = cMap*(1-cMap);
	if (~acl && target != vel){
		acl = .02;
	}
	float next_vel = vel + acl*( target-*start_vel);

	next_vel = MAX(-127.0, next_vel);
	next_vel = MIN(127.0, next_vel);
	motor[nam] = next_vel;
}

task main(){
	float Lstart_vel = 0;
	float Lprev_target = 0;
	float Rstart_vel = 0;
	float Rprev_target = 0;
	float slower_modeoffset = 4;

	while (true){
		float left_target = vexRT[Ch2] + (vexRT[Ch3] / slower_modeoffset);  // left moter forward back
		float right_target = vexRT[Ch2] + (vexRT[Ch3] / slower_modeoffset);  // right moter forward back

		left_target = left_target + vexRT[Ch1] + (vexRT[Ch4] / slower_modeoffset);  // left moter turn offset
		right_target = right_target - vexRT[Ch1] - (vexRT[Ch4] / slower_modeoffset);  // right motar turn offset

		goToTarget(left_target,  leftMotor,  &Lstart_vel, &Lprev_target);
		goToTarget(right_target, rightMotor, &Rstart_vel, &Rprev_target);


		wait1Msec(dt);
	}
}
