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

void getColour(int colourPort, int *colours, int &blue, int &green, int &yellow, 
				int &red)
{
	colours[2] = colours[1];
	colours[1] = colours[0];
	colours[0] = SensorValue[colourPort];

	if (colours[0] == BLUE)
	{
		blue++;
	}
	else if (colours[0] == GREEN)
	{
		green++;
	}
	else if (colours[0] == YELLOW)
	{
		yellow++;
	}
	else if (colours[0] == RED)
	{
		red++;
	}
}

void rotateRamp(int EV3port, int servoNum, int colour)
{
	// Default angle in degrees corresponding to none of the stacks.
	float angle = 0;

	/* Angles below were determined by trial and error and are relative
	to the center default position. */

	if (colour == BLUE)
		angle = 47.27;
	else if (colour == YELLOW)
		angle = 22.23;
	else if (colour == GREEN)
		angle = -15.23;
	else if (colour == RED)
		angle = -38.27;

	setServoPosition(EV3port, servoNum, angle);
	wait1Msec(1500);
}

