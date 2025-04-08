#include "CShapesController.h"
#include <sstream>

CShapesController::CShapesController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "circle", [this]() { AddCircle(); } },
		{ "line", [this]() { AddLine(); } },
		{ "triangle", [this]() { AddTriangle(); } },
		{ "rectangle", [this]() { AddRectangle(); } }
	})
{
}

void CShapesController::HandleUserInput()
{
	std::string command;
	m_input >> command;

	auto it = m_actionMap.find(command);
	if (it != m_actionMap.end())
	{
		try
		{
			it->second;
		}
		catch (const std::exception& e)
		{
			m_output << e.what();
		}
	}
	else
	{
		m_output << "Unknown command " + command + " \n";
	}
}

void CShapesController::AddCircle()
{
	m_output << "\n<fill color> <outline color> <center pos> <radius> \n";
	double radius, x, y;
	std::string fillColor, outlineColor;


}

void CShapesController::AddRectangle()
{
}

void CShapesController::AddTriangle()
{
}

void CShapesController::AddLine()
{
}

uint32_t CShapesController::ColorToInt(const std::string& line)
{
	uint32_t num;
	std::stringstream ss;
	ss << std::hex << line;
	ss >> num;
	return num;
}
