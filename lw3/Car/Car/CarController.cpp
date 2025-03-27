#include "CarController.h"
#include <sstream>

CarController::CarController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "Info", [this](std::istream& input) { Info(input); return true; } },
		{ "EngineOn", [this](std::istream& input) { return EngineOn(input); } },
		{ "EngineOff", [this](std::istream& input) { return EngineOff(input); } },
		{ "SetGear", [this](std::istream& input) { return SetGear(input); } },
		{ "SetSpeed", [this](std::istream& input) { return SetSpeed(input); } }
	})
{
}

void CarController::HandleUserInput(const std::string& line)
{
	std::istringstream str(line);
	std::string command;

	str >> command;	
	auto it = m_actionMap.find(command);
	if (it == m_actionMap.end())
	{
		throw std::runtime_error("Unknown command\n");
	}

	bool commandSucces = it->second(str);
}

void CarController::Info(std::istream& input) const
{
	m_output << "Engine: " << (m_car.IsTurnedOn() ? "on" : "off") << "\n"
		<< "Direction: " << PrintDirection(m_car.GetDirection()) << "\n"
		<< "Speed: " << m_car.GetSpeed() << "\n"
		<< "Gear: " << static_cast<int>(m_car.GetGear()) << "\n";
}

bool CarController::EngineOn(std::istream& input)
{
	return m_car.TurnOnEngine();
}

bool CarController::EngineOff(std::istream& input)
{
	return m_car.TurnOffEngine();
}

int ParseInt(const std::string& str)
{
	size_t pos = 0;
	int value = 0;

	try
	{
		value = std::stoi(str, &pos);
	}
	catch (...) 
	{
		throw std::invalid_argument("Invalid command argument\n");
	}

	if (pos != str.length()) 
	{
		throw std::invalid_argument("Invalid command argument\n");
	}

	return value;
}

bool CarController::SetGear(std::istream& input)
{
	std::string gearStr;
	input >> gearStr;

	try 
	{
		int gear = ParseInt(gearStr);
		return m_car.SetGear(gear);
	}
	catch (const std::exception& e) 
	{
		m_output << e.what();
		return false;
	}
}

bool CarController::SetSpeed(std::istream& input)
{
	std::string speedStr;
	input >> speedStr;

	try 
	{
		int speed = ParseInt(speedStr);
		return m_car.SetSpeed(speed);
	}
	catch (const std::exception& e)
	{
		m_output << e.what();
		return false;
	}
}


std::string CarController::PrintDirection(const Direction& direction) const
{
	switch (direction)
	{
	case Direction::Backward:
		return "backwards";
	case Direction::StandingStill:
		return "standing still";
	case Direction::Forward:
		return "forward";
	default:
		return "Unknow direction";
	}
}
