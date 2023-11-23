void Drive(int speed)//trivial  TESTED
{
	motor[motorA]=motor[motorD]=speed;
}


void Turn(int angle, int speed)//trivial TESTED
{
	if (angle < 0){
		motor[motorA] = speed; //assume counterclockwise is "-"
		motor[motorD] = (-1*speed);
	}

	motor[motorA] = (-1 * speed);
	motor[motorD] = speed;
	while(getGyroDegrees(S4)<(angle))
	{}

}


void claw_axis(bool open){//non-trivial  TESTED
	if (open)//close and go up
	{
		motor[motorC] = -20;
		wait1Msec(2000);
		motor[motorC] = 0;
		
		/* y axis
		motor[motorB] = 20;
		wait1Msec(2000);
		motor[motorB] = 0;
		*/
	} 
	else if (!open)// go down then open
	{
		/* y axis
		motor[motorB] = -20;
		wait1Msec(2000);
		motor[motorB] = 0;
	*/
		motor[motorC] = 20;
		wait1Msec(2000);
		motor[motorC] = 0;
	}
}//void


int stickerColour(){//non-trival  TESTED
int colour;
wait1Msec(1000);
colour = SensorValue[S1];
wait1Msec(1000);

if (colour == 5){//red
	displayString(3, "The color you have selected:");
	displayString(5, "Red");
	wait1Msec(5000);
} else if (colour == 3){
	displayString(3, "The color you have selected:");
	displayString(5, "Green");
} else if (colour == 1){
	displayString(3, "The color you have selected:");
	displayString(5, "Black");
} else {
	colour = 10;
	displayString(3, "No colour detected");
	
	resetGyro(S4);
	motor[motorA]= -12;
	motor[motorD] = 12;
	while(SensorValue[S4] > 180){}
	displayString(3, "Error Code");
	displayString(5, ":10");
	return colour;
}

wait1Msec(5000);
eraseDisplay();

displayString(7, "Enter to continue");
while(!getButtonPress(ENTER_BUTTON)){}
while(getButtonPress(ENTER_BUTTON)){}
return colour;
}//sticker


void goHome(string output, int colour){//non-trivial  NEED WORK
	//follows line backwards
turn(1);
turn(1);
while(SensorValue[S1]!=colour){
	//stops robot
	Drive(0);
	//turns 90 degrees right
	turn(1);
}
//after turn run again
goHome(colour);
//prints string(could be error or success message
displayString(2,output);
}


void followLine(int colour){//non-trivial NEED WORK
if(SensorValue[S1]==colour){
	//start drive
Drive(50);}
ultrasonic(10)
//if break(or turn) loop turns 90 degrees until sensor value is found
int count=0;
while(SensorValue[S1]!=colour){
	//stops robot
	Drive(0);
	//turns 90 degrees right
	turn(1);
	count++;
	//if has turned 4 times there is no line, go back to start
	if(count==4){
		goHome("Cannot find line", colour);
	}

}
//after sensor value is found follow colour again
//if just turned then will still be in correct direction
followLine(colour);
}

int ultrasonic(){// TESTED 
	int const MAX = 30;
	
	if (SensorValue[S2] > MAX){
		return 1;
	}
	
	clearTimer(T1);
	while(time1(T1) <= 5000){
	if (SensorValue[S2] > 30){
	eraseDisplay();
	displayString(3, "Path clear");
	displayString(5, "Enter to continue");
	wait1Msec(1000);
	
	while(!getButtonPress(ENTER_BUTTON)){}
	while(getButtonPress(ENTER_BUTTON)){}
	eraseDisplay();
	return 1;
}//if
	
	}//while
	
	eraseDisplay();
	displayString(3, "Time limit exceeded");
	displayString(5, "Returning home");
	eraseDisplay();
	return 0;
	
}//ultrasonic

void goofy()//non-trivial
{
	if (motor[motorA]==motor[motorD]==0)
{
	motor[motorA]=50;
	motor[motorD]=-50;
	wait1Msec(3000);
	
	motor[motorD]=50;
	motor[motorA]=-50;
	wait1Msec (3000);
	
	motor[motorA]=70;
	motor[motorD]=-70;
	wait1Msec(1000);
	
	motor[motorD]=70;
	motor[motorA]=-70;
	wait1Msec(1000);
	}	
}

int menu(){//non trivial  TESTED 
int packages = 1;
displayString(3, "Please Pick a mode");
displayString(5, "Left Button: PLANE");
displayString(7, "Right Button: # packages");

	while((!getButtonPress(RIGHT_BUTTON))&&(!getButtonPress(LEFT_BUTTON))){}
		if (getButtonPress(RIGHT_BUTTON)){
			eraseDisplay();
			displayString(3, "Num packages: %d", packages);

	while(!getButtonPress(ENTER_BUTTON)){
		if (getButtonPress(UP_BUTTON)){
			eraseDisplay();
			packages++;
			displayString(3, "Num packages: %d", packages);
			wait1Msec(1000);
		}//if

		if (getButtonPress(DOWN_BUTTON)){
			packages--;
			eraseDisplay();

		if (packages <= 0){
			displayString(5, "Packages must be >0");
			displayString(7, "Restarted to 1");
			packages = 1;
		}

	displayString(3, "Num packages: %d", packages);
	wait1Msec(1000);

	}//down

		}//while
		while(getButtonPress(ENTER_BUTTON)){}
}//right button

	if (getButtonPress(LEFT_BUTTON)){
		eraseDisplay();
		packages = 1000;
		displayString(3, "Fully unload plane");
		displayString(5, "Enter to continue");
		while(!getButtonPress(ENTER_BUTTON)){}
		while(getButtonPress(ENTER_BUTTON)){}
		eraseDisplay();
	}

	return packages;
}//menu


task main()
{
	
//COLOUR: S1, S3
//GYRO: S4
//ULTRA: S2
    SensorType[S1] = sensorEV3_Color;
    wait1Msec(50);
    SensorMode[S1] = modeEV3Color_Color;
    wait1Msec(100);

    SensorType[S2] = sensorEV3_Ultrasonic;
    wait1Msec(50);

    SensorType[S3] = sensorEV3_Color;
    wait1Msec(50);
    SensorMode[S3] = modeEV3Color_Color;
    wait1Msec(100);

    SensorType[S4] = sensorEV3_Gyro;
    wait1Msec(50);
    SensorMode[S4] = modeEV3Gyro_Calibration;
    wait1Msec(100);
    SensorMode[S4] = modeEV3Gyro_RateAndAngle;
    wait1Msec(50);

    nMotorEncoder(motorA)=0;
    
while (!getButtonPress(ENTER_BUTTON)){}
while (getButtonPress(ENTER_BUTTON)){}

int packages = menu();

for (int index = 0; index < packages; index++){
	timer1[T1]=0;
	while(timer1[T1]<20000||!getButtonPress(ENTER_BUTTON))
	{
		displayString(3, "%d", timer[t1]);
		if (timer[t1] == 20000){
			eraseDisplay();
			displayString(5, "Time limit has been exceeded");
		}
	}
	
	while(getButtonPress(ENTER_BUTTON)){}
	claw(0);
	while (SensorValue[S4] < 180){
		motor[motorA] = -50;
		motor[motorD] = 50;
	}
	
	int color = stickercolour();
	if (color = 10){
		motor
	}
	followLine(color);
	claw(1);
	goHome();//needs further attention
	
	
	
	
}//for

goofy();

}//task main






/*FUNCTIONS

main: get box coolour input to follow line function

go back to original position

Drive
- speed(+,-)

turn left,right
- left or right


Follow line
- colour of correct line
*drive forward on line until line stops, checks if there is line on left or right turns and repeat


Claw open close
- parameter for open or close

senses box colour
* check colour of sticker
* return sticker colour

finds correct line
- box sticker colour
* drives forward on black line
* when sees input colour it turns
* call follow line function


----
press button
turns on

drive forward

picks up box

senses box colour

finds coresponding line

drives on line
makes turns if needed

goes back if needed
stops if needed
senses drop zone

drops baggage in zone

turns atound and follows line back to original position
waits to sense new package in loading zone
if sees repeat, if not turns off

*/
