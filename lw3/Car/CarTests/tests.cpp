#define CATCH_CONFIG_MAIN
#include <iostream>
#include <catch.hpp>
#include <Car.h>

// check range speed

TEST_CASE("Uniform shifting across 1-5 gears")
{
	Car car;
	car.TurnOnEngine();
	CHECK(car.IsTurnedOn());

	car.SetGear(1);
	CHECK(car.GetGear() == Gear::FirstGear);
	car.SetSpeed(20);
	CHECK(car.GetSpeed() == 20);
	CHECK_THROWS_AS(car.SetSpeed(40), std::runtime_error);

	car.SetGear(2);
	CHECK(car.GetGear() == Gear::SecondGear);
	car.SetSpeed(30);
	CHECK(car.GetSpeed() == 30);
	CHECK_THROWS_AS(car.SetSpeed(60), std::runtime_error);

	car.SetGear(3);
	CHECK(car.GetGear() == Gear::ThirdGear);
	car.SetSpeed(50);
	CHECK(car.GetSpeed() == 50);
	CHECK_THROWS_AS(car.SetSpeed(80), std::runtime_error);

	car.SetGear(4);
	CHECK(car.GetGear() == Gear::FourthGear);
	car.SetSpeed(90);
	CHECK(car.GetSpeed() == 90);
	CHECK_THROWS_AS(car.SetSpeed(100), std::runtime_error);

	car.SetGear(5);
	CHECK(car.GetGear() == Gear::FifthGear);
	car.SetSpeed(150);
	CHECK(car.GetSpeed() == 150);
	CHECK_THROWS_AS(car.SetSpeed(200), std::runtime_error);
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
	CHECK_THROWS_AS(car.SetSpeed(25), std::runtime_error);
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
	CHECK_THROWS_AS(car.SetSpeed(60), std::runtime_error);
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
		CHECK_THROWS_AS(car.SetGear(1), std::runtime_error);
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
	CHECK_THROWS_AS(car.SetGear(4), std::runtime_error);
	CHECK_THROWS_AS(car.SetSpeed(20), std::runtime_error);
	CHECK(car.GetSpeed() == 0);
}

TEST_CASE("Checking for correct input of values")
{
	Car car;
	car.TurnOnEngine();
	CHECK_THROWS_AS(car.SetSpeed(-5), std::runtime_error);
	CHECK(car.GetSpeed() == 0);
	CHECK_THROWS_AS(car.SetGear(10), std::runtime_error);
	CHECK(car.GetGear() == Gear::NeutralGear);
}

TEST_CASE("Checking engine turn on twice")
{
	Car car;
	car.TurnOnEngine();
	CHECK(car.IsTurnedOn());
	car.TurnOnEngine();
	CHECK(car.IsTurnedOn());
}

TEST_CASE("Checking engine turn off twice")
{
	Car car;
	car.TurnOffEngine();
	CHECK(!car.IsTurnedOn());
	car.TurnOffEngine();
	CHECK(!car.IsTurnedOn());
}

// включили двигатель 2 раза
// макс мин скорости на каждой передаче