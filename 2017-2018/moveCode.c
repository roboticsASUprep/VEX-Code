#pragma config(Sensor, dgtl1,  reverseOn,      sensorDigitalOut)
#pragma config(Sensor, dgtl2,  reverseOff,     sensorDigitalOut)
#pragma config(Sensor, dgtl3,  forkSwitch,     sensorTouch)
#pragma config(Sensor, dgtl4,  armSwitch,      sensorTouch)
#pragma config(Sensor, dgtl5,  sideControl,    sensorDigitalIn)
#pragma config(Motor,  port2,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           arm2,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           fLbL,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           pusherMotor,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           forkLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           forkRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           arm1,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           fRbR,          tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

task autonomous()
{
	//lower fork
	motor[arm1] = 75;
	motor[arm2] = 75;
	motor[forkLeft] = 120;
	motor[forkRight] = 120;
	wait1Msec(1500);
	//stop fork; move forward
	motor[forkLeft]= 0;
	motor[forkRight] = 0;
	motor[fLbL] = 127;
	motor[fRbR] = 127;
	wait1Msec(1750);
	//stop moving
	motor[fRbR] = 0;
	motor[fLbL] = 0;
	//raise fork
	motor[forkLeft] = -127;
	motor[forkRight] = -127;
	motor[arm1] = -45;
	motor[arm2] = -45;
	wait1Msec(1950);
	motor[forkLeft] = 0;
	motor[forkRight] = 0;
	//back out (reverse)
	motor[fRbR] = -120;
	motor[fLbL] = -120;
	wait1Msec(1500);
	//stop motors; lower forks
	motor[fRbR] = -120;
	motor[fLbL] = 80;
	wait1Msec(750);
	motor[fRbR] = 120;
	motor[fLbL] = 120;
	wait1Msec(500);
	motor[fRbR] = -120;
	motor[fLbL] = 80;
	wait1Msec(600);
	motor[fRbR] = 120;
	motor[fLbL] = 120;
	motor[arm1] = 75;
	motor[arm2] = 75;
	wait1Msec(1350);
	motor[fLbL] = 0;
	motor[fRbR] = 0;
	motor[pusherMotor] = 80;
	motor[forkLeft] = 127;
	motor[forkRight] = 127;
	wait1Msec(1550);
	motor[fLbL] = -120;
	motor[fRbR] = -120;
	motor[forkLeft] = -50;
	motor[forkRight] = -50;
	wait1Msec(800);
	//stop motors
	motor[forkLeft] = 0;
	motor[forkRight] = 0;
	motor[fLbL] = 0;
	motor[fRbR] = 0;



	//set up for 10
	/*
	motor[forkLeft] = 80;
	motor[forkRight] = 80;
	wait1Msec(2000);
	motor[forkLeft] = 0;
	motor[forkRight] = 0;
	//bring cone down
	wait1Msec(100);
	motor[fLbL] = -80;
	motor[fRbR] = -120;
	wait1Msec(1000);
	motor[fLbL] = 0;
	motor[fRbR] = 0;
	*/

}

task usercontrol() {
	bool pressed = false;
	int motorSwitch = 1;

	while(true)	{
		if(vexRT[Btn7L]) {
			if(!pressed) {
				motorSwitch *= -1;
			}
			pressed = true;
			} else {
			pressed = false;
		}
		motor(fRbR) = (vexRT[Ch3] * motorSwitch) - vexRT[Ch4];
		motor(fLbL) = (vexRT[Ch3] * motorSwitch) + vexRT[Ch4];

		motor(forkRight) = vexRT[Ch2] * !SensorValue(forkSwitch);
		motor(forkLeft) = vexRT[Ch2] * !SensorValue(forkSwitch);

		motor(pusherMotor) = (126 * vexRT[Btn8U]) - (122 * vexRT[Btn8D]);

		//motor(turnTable) = (80 * vexRT[Btn7L]) - (80 * vexRT[Btn7R]);

		motor(arm1) = (115 * vexRT[Btn6U]) - (115 * vexRT[Btn6D]);
		motor(arm2) = (115 * vexRT[Btn6U]) - (115 * vexRT[Btn6D]);
		motor(claw) = (90 * vexRT[Btn8L]) - (90 * vexRT[Btn8R]);

		//if(motorSwitch == -1) {
		//	SensorValue[reverseOn] = true;
		//	SensorValue[reverseOff] = false;
		//	}	else if(motorSwitch == 1) {
		//	SensorValue[reverseOn] = false;
		//	SensorValue[reverseOff] = true;
		//}
	}
}
