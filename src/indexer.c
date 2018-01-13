void checkJamOrSorted(int port, float distance, bool &jam, bool &sorted)
{
	const int SENSOR_TOL = 0.2;

	jam = (abs(SensorValue[port] - distance) < SENSOR_TOL);
	/* If the distance remains constant (conveyor doesn't move),
	then jam is set to true. */

	// Candy's approximate distance from the ultrasonic sensor
	const int CANDY_DIST = 4.7;	

	if (sorted)
		sorted =  !(SensorValue[port] <= CANDY_DIST);
		/* If the sensor value detects a candy then sorted is set to false.
		Does not check again during one interation of the moveConveyor if a
		candy is detected at any point. */
}

void moveConveyor(int motorPort, int ultrasonicPort, bool &jam, bool &sorted, 
					int iteration)
{
	float initialDist = SensorValue[ultrasonicPort];

	sorted = true;	// Assumes that all the candy has been sorted.

	/* Because of the mechanical design of the conveyor belt, it was impossible
	to achieve an even number of placeholders for the gumballs. Hence, there is
	a shorter than usual distance between just two placeholders on the entire
	conveyor belt that occurs every 16 iterations. */
	const float ENC_STD = 2.58 * 360 / (2 * PI * 1.35);	// Standard ENC_LIMIT
	const float ENC_16TH = ENC_STD - (ENC_STD / 3); // Every 16th ENC_LIMIT
	float ENC_LIMIT = 0;
	if (iteration % 16 != 0)
	{
		ENC_LIMIT = ENC_STD;
	}
	else
	{
		ENC_LIMIT = ENC_16TH;
	}

	nMotorEncoder[motorPort] = 0;
	motor[motorPort] = 15;

	while ((nMotorEncoder[motorPort] < ENC_LIMIT) && !jam)
	{
		checkJamOrSorted(ultrasonicPort, initialDist, jam, sorted);
	}

	motor[motorPort] = 0;
}

