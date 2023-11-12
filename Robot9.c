
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
}

void Drive(int speed)
{
while (nMotorEncoder[motorA]==
	(
	motor[motorA]=motor[motorD]=speed;
	)

	motor[motorA]=motor[motorD]=0;
}

void Turn(int angle, int speed){
	if (angle < 0){
		motor[motorA] = speed; //assume counterclockwise is "-"
		motor[motorD] = (-1*speed);
	}
	
	motor[motorA] = (-1 * speed);
	motor[motorD] = speed;
	while(getGyroDegrees(S4)<(angle))
	{}
	
}

void followLine(int colour)
{
	}
void Claw(bool open_or_close){
	}

int stickerColour(int colour)
{
	if (SensorValue[S1]==5)
	{
	colour=5;
	}
	if (SensorValue[S1]==4)
	{
	colour=4;
	}
	if (SensorValue[S1]==3)
	{
	colour=3;
	}
	if (SensorValue[S1]==2)
	{
	colour=2;
	}
	else
	{
		displayString(5,"No colour")
	}
		return colour;
/*
if (SensorValue[S1]==colour)
{
	displayString(5,"Colour: ");
		colour=colour1;
}

if (SensorValue[S1]==colour2)
{
	displayString(5,"Colour: ");
		colour=colour2;
}
if (SensorValue[S1]==colour3)
{
	displayString(5,"Colour: ");
		colour=colour3;
}
if (SensorValue[S1]==colour4)
{
	displayString(5,"Colour: ");
	colour=colour4;
}
if (SensorValue[S1]==0]
{
	displayString(5,"No Colour");
	colour=0;
}

return colour
*/
}

void findLine(int colour)
{



}
void goHome(string output, int colour){
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

void followLine(int colour){
if(SensorValue[S1]==colour){
	//start drive
Drive(50);}
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

void turn(int angle, int speed){
	if (angle < 0){
		motor[motorA] = speed; //assume counterclockwise is "-"
		motor[motorD] = (-1*speed);
	}
	
	motor[motorA] = (-1 * speed);
	motor[motorD] = speed;
	while(getGyroDegrees(S4)<(angle))
	{}
	
}

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
