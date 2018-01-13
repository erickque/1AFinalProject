#include "EV3Servo-lib-UW.c"
#include "indexer.c"
#include "sorter.c"
#include "IO.c"
#include "dispenser.c"

task main()
{
	SensorType[S1] = sensorEV3_Ultrasonic;
	SensorType[S2] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S2] = modeEV3Color_Color;
	wait1Msec(50);
	SensorType[S3] = sensorEV3_Touch;
	SensorType[S4] = sensorI2CCustom9V;

	int colours[3] = {0, 0, 0};

	// number of each colour of candy available
	int blue = 0, green = 0, yellow = 0, red = 0;

	displayString(0,"Place candies in the funnel.");
	displayString(1,"Press enter when complete.");

	while(!getButtonPress(buttonEnter))
	{}
	while(getButtonPress(buttonEnter))
	{}

	eraseDisplay();
	displayString(0, "Sorting.");

	bool jam = false, sorted = false;
	int sortedCount = 0;
	int iteration = 0;

	time1[T1] = 0;

	while (!jam && sortedCount < 5)
	{
		getColour(S2, colours, blue, green, yellow, red);
		wait1Msec(500);
		rotateRamp(S4, 4, colours[1]);
		moveConveyor(motorA, S1, jam, sorted, iteration);
		if (sorted)
		{
			sortedCount++;
		}
		else
		{
			sortedCount = 0;
		}
		iteration++;
	}

	int time = time1[T1]/1000;


	displayString(0, "Sorting completed in %d s", time);
	displayString(1, "Press enter to");
	displayString(2, "start dispensing.");

	while(!getButtonPress(buttonEnter))
	{}
	while(getButtonPress(buttonEnter))
	{}

	eraseDisplay();

	while ((blue+green+yellow+red) > 0)
	{

		COLOUR candyColour = 0;

		output(blue, green, yellow, red);

		displayString(6, "Please select the candy colour");
		displayString(7, "you would like.");
		do
		{
			candyColour = getInput(blue, green, yellow, red);
		}
		while (candyColour == 0);

		dispense(candyColour, motorC, motorD);

		eraseDisplay();	
	}

	displayString(0, "Dispensing is complete.");
	displayString(1, "Press enter to end.");

	while(!getButtonPress(buttonEnter))
	{}
	while(getButtonPress(buttonEnter))
	{}
}
