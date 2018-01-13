#ifndef _COLOURS
#define _COLOURS

enum COLOUR 
{
	BLUE = 2, 
	GREEN = 3, 
	YELLOW = 4, 
	RED = 5
};

#endif

void output(int blue, int green, int yellow, int red)
{
	displayString(0, "Candies left of each colour:");
	displayString(1, "Blue: %d", blue);
	displayString(2, "Green: %d", green);
	displayString(3, "Yellow: %d", yellow);
	displayString(4, "Red: %d", red);
}

int getInput(int & blue, int & green, int & yellow, int & red)
{
	while (!getButtonPress(buttonRight) && !getButtonPress(buttonLeft)
		&& !getButtonPress(buttonUp) && !getButtonPress(buttonDown))
	{
		// Waits until one of the buttons corresponding to a colour are pressed.
	}
	if (getButtonPress(buttonRight))
	{
		if (blue > 0)
		{
			blue--;
			return BLUE;
		}
	}
	else if (getButtonPress(buttonLeft))
	{
		if (green > 0)
		{
			green--;
			return GREEN;
		}
	}
	else if (getButtonPress(buttonUp))
	{
		if (yellow > 0)
		{
			yellow--;
			return YELLOW;
		}
	}
	else 
	{
		if (red > 0)
		{
			red--;
			return RED;
		}
	}
	displayString(6, "There are no more of these.");
	displayString(7, "Please pick another colour.");
	return 0;
}

