#pragma config(Motor,  port1,           motrev,        tmotorVex393_MC29, openLoop)
// get ide here http://www.robotc.net/
task main(){

	while(true)
	{
			motor[motrev] = 20;  // (y - x)/2
	}
}
