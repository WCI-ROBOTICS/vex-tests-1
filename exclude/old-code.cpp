#pragma config(Motor,  port8,           motrev,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           mot,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           clawrot,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex393, openLoop, reversed)
//Michael figure out the wheel and claw ports

void writeArm(int speed){
	motor[mot] = speed;
	motor[motrev] = speed;
}

task main(){
	int armSpeed = 127;
	int armSlow = 64;
	int clawSpeed = 100;
	int clawSlow = 20;
	int clawrotSpeed = 100;
	int clawrotSlow = 50;
	bool moving = false;
	bool movingSlow = false;

	while(1 == 1)
	{
		//Fast mode
		if(vexRT[Ch2] != 0 || vexRT[Ch1] != 0){
			motor[leftMotor]  = (vexRT[Ch2] + vexRT[Ch1]);  // (y + x)/2
			motor[rightMotor] = (vexRT[Ch2] - vexRT[Ch1]);  // (y - x)/2
			} else if(vexRT[Ch3] != 0 || vexRT[Ch4] != 0){
			//Slow mode
			motor[leftMotor]  = (vexRT[Ch3] + vexRT[Ch4])/4;  // (y + x)/4
			motor[rightMotor] = (vexRT[Ch3] - vexRT[Ch4])/4;  // (y - x)/4
			} else {
			motor[leftMotor]  = 0;
			motor[rightMotor] = 0;
		}

		//Fast mode
		if(movingSlow == false){
			if(vexRT[Btn8U] == 1)           //If button 8U is pressed...
			{
				writeArm(armSpeed);        //...raise the arm.
				moving = true;
			}
			else if(vexRT[Btn8D] == 1)      //Else, if button 8D is pressed...
			{
				writeArm(armSpeed * -1);       //...lower the arm.
				moving = true;
			}
			else                              //Else (neither button is pressed)...
			{
				writeArm(0);          //...stop the arm.
				moving = false;
			}

			// Open, close or do not more claw
			if(vexRT[Btn8R] == 1)           //If Button 8R is pressed...
			{
				motor[claw] = clawSpeed;          //spin the claw.
			}
			else if(vexRT[Btn8L] == 1)      //Else, if button 8L is pressed...
			{
				motor[claw] = clawSpeed * -1;         //spin the other way.
			}
			else                              //Else (neither button is pressed)...
			{
				motor[claw] = 0;            //...stop the claw.
			}
			//vertical rotation
			if(vexRT[Btn6U] == 1)           //If Button 8R is pressed...
			{
				motor[clawrot] = clawrotSpeed;          //spin the claw.
			}
			else if(vexRT[Btn6D] == 1)      //Else, if button 8L is pressed...
			{
				motor[clawrot] = clawrotSpeed * -1;         //spin the other way.
			}
			else                              //Else (neither button is pressed)...
			{
				motor[clawrot] = 0;            //...stop the claw.
			}
		}

		//Slow mode
		if(moving == false){
			if(vexRT[Btn7U] == 1)           //If button 8U is pressed...
			{
				writeArm(armSlow);        //...raise the arm.
				movingSlow = true;
			}
			else if(vexRT[Btn7D] == 1)      //Else, if button 8D is pressed...
			{
				writeArm(armSlow * -1);       //...lower the arm.
				movingSlow = true;
			}
			else                              //Else (neither button is pressed)...
			{
				writeArm(0);          //...stop the arm.
				movingSlow = false;
			}

			// Open, close or do not more claw
			if(vexRT[Btn7R] == 1)           //If Button 8R is pressed...
			{
				motor[claw] = clawSlow;          //spin the claw.
			}
			else if(vexRT[Btn7L] == 1)      //Else, if button 8L is pressed...
			{
				motor[claw] = clawSlow * -1;         //spin the other way.
			}
			else                              //Else (neither button is pressed)...
			{
				motor[claw] = 0;            //...stop the claw.
			}

			//vertical rotation
			if(vexRT[Btn5U] == 1)           //If Button 8R is pressed...
			{
				motor[clawrot] = clawrotSlow;          //spin the claw.
			}
			else if(vexRT[Btn5D] == 1)      //Else, if button 8L is pressed...
			{
				motor[clawrot] = clawrotSlow * -1;         //spin the other way.
			}
			else                              //Else (neither button is pressed)...
			{
				motor[clawrot] = 0;            //...stop the claw.
			}


		}
	}
}
