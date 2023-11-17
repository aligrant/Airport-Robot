	
int menu(){
	displayString(3, "Please Pick a mode");
	displayString(5, "Left Button for constant delivery");
	displayString(7, "Right Button for numbered packages");
	
	if (getButtonPress(RIGHT_BUTTON))//numbered packages
	{
		while (!getButtonPress(ENTER_BUTTON)){
		if (getButtonPress(BUTTON_UP))
		{
			packages++;
		}
		
		if (getButtonPress(BUTTON_DOWN))
		{
			packages--;
		}
		
		}//while
	}//right button
	
	
	
	if (getButtonPress(LEFT_BUTTON))
	{
		
	}
	
	
	
	
	displayString(5, "How many packages? (1 - 3)");
	
}//menu







task main(){
	while(!getButtonPress(ENTER_BUTTON))
	{}
	while(getButtonPress(ENTER_BUTTON))
	{}	
	
	int packages = 0;
	menu(packages);
	
	
	
	
	
}