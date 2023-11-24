void Stop(){
	motor[motorA]=motor[motorD]=0;
	return;
}

void turn(int angle, int speed){
	resetGyro(S4);
	if (-angle < 0){//right
		motor[motorA] = speed; //assume counterclockwise is "-"
		motor[motorD] = 0;
		while(getGyroDegrees(S4)<(angle))
		{}
	}
	else{//left
		motor[motorA] =-speed;
		motor[motorD] = 0;
		while(getGyroDegrees(S4)>(angle))
		{}
	}

	Stop();
}

void followLine(int colour)//tested :)
{
	float TO_CM = 2*PI*2.75/360;
	float dist_to_line=1;
	if(SensorValue[S3]!=colour){
		motor[motorA]=motor[motorD]=1;
		while(SensorValue[S3]!=colour){}
	}
	turn(45,50);
	//drive 10cm
	for(int count=0; count<300||SensorValue[S3]==1;count++){//exit loop when reaches the different colour as well
		nMotorEncoder[motorD]=0;
		motor[motorA]=motor[motorD]=20;
		while(nMotorEncoder[motorD]*TO_CM<5){}
		displayString(3,"more than 5");
		Stop();
		turn(-75,50);
		motor[motorA]=motor[motorD]=20;
		while(SensorValue[S3]!=colour){}
		Stop();
		float dist_to_line=nMotorEncoder[motorD]*TO_CM;
		float angle=atan(10/dist_to_line)*180/PI;
		//float angle = asin((5*sin(135))/(sqrt(25+(pow(dist_to_line,2)+10*dist_to_line)))*180/PI;
		turn(2*angle,50);

	}
}//add different colour at destination to stop followline

void Drive(int speed)//trivial  TESTED
{
	motor[motorA]=motor[motorD]=speed;
}

void claw(bool open){//non-trivial  TESTED
	if (open)//close and go up
	{
		motor[motorC] = -20;
		wait1Msec(2000);
		motor[motorC] = 0;

	
		motor[motorB] = 20;
		wait1Msec(2000);
		motor[motorB] = 0;
		
	}
	else if (!open)// go down then open
	{
		
		motor[motorB] = -20;
		wait1Msec(2000);
		motor[motorB] = 0;
		
		motor[motorC] = 20;
		wait1Msec(2000);
		motor[motorC] = 0;
	}
}//void


int stickerColour(){//non-trival  TESTED
	int colour;
	colour = SensorValue[S1];
	wait1Msec(1000);

	if (colour == 5)
	{//red
		displayString(3, "The color you have selected:");
		displayString(5, "Red");
		wait1Msec(5000);
		} 
		else if (colour == 3)
		{
		displayString(3, "The color you have selected:");
		displayString(5, "Green");
		wait1Msec(5000);
		} 
		else if (colour == 1)
		{
		displayString(3, "The color you have selected:");
		displayString(5, "Black");
		wait1Msec(5000);
		} 
		else 
		{
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

	wait1Msec(500);
	eraseDisplay();
	displayString(7, "Enter to continue");
	while(!getButtonPress(ENTER_BUTTON)){}
	while(getButtonPress(ENTER_BUTTON)){}
	return colour;
}//sticker


void goHome(string output, int colour){//trivial  NEED WORK
	//follows line backwards
	turn(180,50);
	followLine(colour);
		//turns 90 degrees right
		turn(-90,50);
		Drive(50);
	}
	//after turn run again
	goHome(colour);
	//prints string(could be error or success message
	displayString(2,output);
}

int ultrasonic(){// TESTED
	int const MAX = 30;
	if (SensorValue[S2] > MAX){
		return 1;
	}

	clearTimer(T2);
	while(time2(T2) <= 5000){
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

void goofy(int colour)//non-trivial
{
	if (colour==1)
	{
		displayString(5, "HOORAY BLACK PACKAGE DELIVERED");
		motor[motorA]=50;
		motor[motorD]=-50;
		wait1Msec(3000);

		motor[motorD]=50;
		motor[motorA]=-50;
		wait1Msec (3000);
		eraseDisplay();
}
if (colour==3)
{
		displayString(5, "HOORAY GREEN PACKAGE DELIVERED");
		motor[motorA]=70;
		motor[motorD]=-70;
		wait1Msec(1000);

		motor[motorD]=70;
		motor[motorA]=-70;
		wait1Msec(1000);
		eraseDisplay();
	}
	if (colour==5)
	{
		displayString(5, "HOORAY RED PACKAGE DELIVERED");
		Drive(50);
		wait1Msec(1000);
		Drive(-50);
		wait1Msec(1000);
		resetGyro(S4);
		while (getGyroDegrees<360){
		motor[motorA]=50;
		motor[motorD]=-50;
	}
	Drive(0);
		eraseDisplay();
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

void findline(int colour)
{
	Drive(50);
	while (sensorValue[S3]!=colour){}
	turn(90,50);

}

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
	int exitValue = 0;
	for (int index = 0; index < packages && exitValue < 1; index++){
		

		clearTimer(T1);
		displayString(3, "Press Enter to Start");
		while (time1[1] <= 5000){
			displayString(3, "Time: %d", time1[T1]/1000 )
			wait1Msec(500);
		}
		if (time1 == 5000){
			eraseDisplay();
			displayString(5, "Time limit exceeded");
			exitValue = 1;
		}
		while(!getButtonPress(ENTER_BUTTON)){}
		while(getButtonPress(ENTER_BUTTON)){}
	
		Drive(10);
		while(SensorValue[S3] == 2){}
		claw(1);//value is true, claw clses and picks up object
		wait1Msec(1000);
		
		int color = stickercolour();
		if (color == 10){
			Stop();
			wait1Msec(1000);
			timerValue = 1;
		}
		findline(color);
		followLine(color);
		claw(0);
		goHome();//needs further attention
		goofy();
	}//for
	
	if (exitValue == 1){
		eraseDisplay();
		wait1Msec(1000);
		displayString(5, "An Error Occured!");
		displayString(7, "Please try again!");
	} else {
		eraseDisplay();
		wait1Msec(1000);
		displayString(5, "Packages delivered!");
		displayString(7, "YIPEEEEEE");
	}
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
