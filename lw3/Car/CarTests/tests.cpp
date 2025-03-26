#define CATCH_CONFIG_MAIN
#include <iostream>
#include <catch.hpp>
#include <Car.h>


TEST_CASE("Uniform shifting across 1-5 gears")
{
	Car car;
	car.TurnOnEngine();
	CHECK(car.IsTurnedOn());

	car.SetGear(1);
	CHECK(car.GetGear() == Gear::FirstGear);
	car.SetSpeed(20);
	CHECK(car.GetSpeed() == 20);
	car.SetSpeed(40);
	CHECK(car.GetSpeed() == 20);

	car.SetGear(2);
	CHECK(car.GetGear() == Gear::SecondGear);
	car.SetSpeed(30);
	CHECK(car.GetSpeed() == 30);
	car.SetSpeed(60);
	CHECK(car.GetSpeed() == 30);

	car.SetGear(3);
	CHECK(car.GetGear() == Gear::ThirdGear);
	car.SetSpeed(50);
	CHECK(car.GetSpeed() == 50);
	car.SetSpeed(80);
	CHECK(car.GetSpeed() == 50);

	car.SetGear(4);
	CHECK(car.GetGear() == Gear::FourthGear);
	car.SetSpeed(90);
	CHECK(car.GetSpeed() == 90);
	car.SetSpeed(100);
	CHECK(car.GetSpeed() == 90);

	car.SetGear(5);
	CHECK(car.GetGear() == Gear::FifthGear);
	car.SetSpeed(150);
	CHECK(car.GetSpeed() == 150);
	car.SetSpeed(200);
	CHECK(car.GetSpeed() == 150);
}

TEST_CASE("Switching speeds if we're going backwards in neutral gear")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(20);
	car.SetGear(1);
	CHECK(car.GetGear() == Gear::ReverseGear);
	car.SetGear(2);
	CHECK(car.GetGear() == Gear::ReverseGear);
	car.SetGear(0);
	CHECK(car.GetGear() == Gear::NeutralGear);
	car.SetSpeed(19);
	CHECK(car.GetSpeed() == 19);
	car.SetSpeed(25);
	CHECK(car.GetSpeed() == 19);
}

TEST_CASE("Neutral transmission check")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(2);
	car.SetSpeed(50);
	car.SetGear(0);
	CHECK(car.GetGear() == Gear::NeutralGear);
	car.SetSpeed(60);
	CHECK(car.GetSpeed() == 50);
	car.SetSpeed(0);
	CHECK(car.GetSpeed() == 0);
}

TEST_CASE("Checking the switching conditions on ReverseGear, NeutralGear, FirstGear")
{
	Car car;
	car.TurnOnEngine();
	CHECK(car.IsTurnedOn());

	SECTION("Switch on reverse gear from first gear")
	{
		car.SetGear(1);
		CHECK(car.GetGear() == Gear::FirstGear);
		car.SetSpeed(10);
		CHECK(car.GetSpeed() == 10);
		car.SetGear(-1);
		CHECK(car.GetGear() == Gear::FirstGear);
	}

	SECTION("Switch on neutral gear from reverse gear")
	{
		car.SetSpeed(0);
		CHECK(car.GetSpeed() == 0);
		car.SetGear(-1);
		CHECK(car.GetGear() == Gear::ReverseGear);
		car.SetSpeed(10);
		CHECK(car.GetSpeed() == 10);
		car.SetGear(1);
		CHECK(car.GetGear() == Gear::ReverseGear);
		car.SetGear(0);
		CHECK(car.GetGear() == Gear::NeutralGear);
		car.SetGear(1);
		CHECK(car.GetGear() == Gear::NeutralGear);
		car.SetGear(-1);
		CHECK(car.GetGear() == Gear::NeutralGear);
	}
}

TEST_CASE("Checking the gear shift with the engine off")
{
	Car car;
	car.SetGear(0);
	CHECK(car.GetGear() == Gear::NeutralGear);
	car.SetGear(4);
	CHECK(car.GetGear() == Gear::NeutralGear);
	car.SetSpeed(20);
	CHECK(car.GetSpeed() == 0);
}

TEST_CASE("Checking for correct input of values")
{
	Car car;
	car.TurnOnEngine();
	car.SetSpeed(-5);
	CHECK(car.GetSpeed() == 0);
	car.SetGear(10);
	CHECK(car.GetGear() == Gear::NeutralGear);
}