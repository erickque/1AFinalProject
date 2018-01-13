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

void dispense(int colour, int basePort, int pistonPort)
{

	const int ENC_BLUE = 42;
	const int ENC_YELLOW = 17;
	const int ENC_GREEN = 26;
	const int ENC_RED = 57;
	const int ENC_PISTON = 6000;

	int ENC_LIMIT = 0;

	if (colour == BLUE)
	{
		ENC_LIMIT = ENC_BLUE;
	}
	else if (colour == GREEN)
	{
		ENC_LIMIT = ENC_GREEN;
	}
	else if (colour == YELLOW)
	{
		ENC_LIMIT = ENC_YELLOW;
	}
	else if (colour == RED)
	{
		ENC_LIMIT = ENC_RED;
	}

	nMotorEncoder[basePort] = 0;

	/* Colours corresponding to even numbers (blue and yellow) were placed on
	one side of the piston, and colours corresponding to odd numbers were
	placed on the other. Thus, the direction the piston spins can be determined
	by raising -1 to the power of the colour number, an even number resulting
	in the positive direction, and an odd number in the negative. */
	motor[basePort] = pow(-1,colour)*5;

	while (abs(nMotorEncoder[basePort]) < ENC_LIMIT)
	{}

	motor[basePort] = 0;

	wait1Msec(500);

	motor[pistonPort] = 80;
	nMotorEncoder[pistonPort] = 0;
	while (abs(nMotorEncoder[pistonPort]) < ENC_PISTON)
	{}
	motor[pistonPort] = 0;

	nMotorEncoder[pistonPort] = 0;
	motor[pistonPort] = -80;
	while (abs(nMotorEncoder[pistonPort]) < ENC_PISTON)
	{}
	motor[pistonPort] = 0;

	wait1Msec(500);

	nMotorEncoder[basePort] = 0;
	motor[basePort] = pow(-1, colour + 1)*5;
	while (abs(nMotorEncoder[basePort]) < ENC_LIMIT)
	{}
	motor[basePort] = 0;
}