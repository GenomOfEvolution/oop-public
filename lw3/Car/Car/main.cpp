#include "Car.h"
#include <iostream>

int main()
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(20);
	car.SetGear(1);
	car.SetGear(2);
	car.SetGear(0);
	car.SetSpeed(19);
	car.SetSpeed(25);

	return EXIT_SUCCESS;
}