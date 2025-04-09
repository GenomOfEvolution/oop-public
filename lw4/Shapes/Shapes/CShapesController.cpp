#include "CShapesController.h"
#include "CCircle.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CCanvas.h"

#include <sstream>
#include <regex>


bool IsValidColorFormat(const std::string& colorStr)
{
	static const std::regex colorRegex("^[0-9a-fA-F]{6}$");
	return std::regex_match(colorStr, colorRegex);
}

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
			it->second();
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

IShape* CShapesController::GetShapeWithMaxArea() const
{
	auto result = std::max_element(m_shapes.begin(), m_shapes.end(), [](auto& a, auto& b) {
		return a->GetArea() < b->GetArea();
		});

	if (result != m_shapes.end())
	{
		return result->get();
	}

	return nullptr;
}


IShape* CShapesController::GetShapeWithMinPerimeter() const
{
	auto result = std::min_element(m_shapes.begin(), m_shapes.end(), [](auto& a, auto& b) {
		return a->GetPerimeter() < b->GetPerimeter();
		});

	if (result != m_shapes.end())
	{
		return result->get();
	}

	return nullptr;
}

void CShapesController::PrintTaskResult()
{
	if (m_shapes.empty())
	{
		m_output << "No shapes" << std::endl;
		return;
	}

	m_output << "Shape with max area: \n";
	auto maxAreaShape = GetShapeWithMaxArea();
	m_output << maxAreaShape->ToString();

	m_output << "\nShape with min perimeter: \n";
	auto minPerimetrShape = GetShapeWithMinPerimeter();
	m_output << minPerimetrShape->ToString();
}

void CShapesController::AddCircle()
{
	m_output << "\n<fill color> <outline color> <center pos> <radius> \n";
	double radius, x, y;
	std::string fillColorStr, outlineColorStr;

	if (!(m_input >> fillColorStr >> outlineColorStr >> x >> y >> radius))
	{
		throw std::invalid_argument("Invalid input format. Expected: RRGGBB RRGGBB x y radius");
	}

	if (!IsValidColorFormat(fillColorStr) || !IsValidColorFormat(outlineColorStr))
	{
		throw std::invalid_argument("Invalid color format");
	}

	uint32_t fillColor = ColorToInt(fillColorStr);
	uint32_t outlineColor = ColorToInt(outlineColorStr);

	if (radius <= 0)
	{
		throw std::invalid_argument("Radius should be greater than 0");
	}

	auto circle = std::make_unique<CCircle>(CPoint(x, y), radius, fillColor, outlineColor);
	m_shapes.push_back(std::move(circle));
}

void CShapesController::AddRectangle()
{
	m_output << "\n<fill color> <outline color> <left top pos> <width> <height>\n";
	
	std::string fillColorStr, outlineColorStr;
	double x, y, width, height;

	if (!(m_input >> fillColorStr >> outlineColorStr >> x >> y >> width >> height))
	{
		throw std::invalid_argument("Invalid input format. Expected: RRGGBB RRGGBB x y width height");
	}

	if (!IsValidColorFormat(fillColorStr) || !IsValidColorFormat(outlineColorStr))
	{
		throw std::invalid_argument("Invalid color format");
	}

	uint32_t fillColor = ColorToInt(fillColorStr);
	uint32_t outlineColor = ColorToInt(outlineColorStr);

	if (width <= 0)
	{
		throw std::invalid_argument("Width must be positive");
	}

	if (height <= 0)
	{
		throw std::invalid_argument("Height must be positive");
	}

	auto rectangle = std::make_unique<CRectangle>(CPoint(x, y), width, height, fillColor, outlineColor);
	m_shapes.push_back(std::move(rectangle));
}

void CShapesController::AddTriangle()
{
	m_output << "\n<fill color> <outline color> <3 vertces positions>\n";

	std::string fillColorStr, outlineColorStr;
	double x1, y1, x2, y2, x3, y3;

	if (!(m_input >> fillColorStr >> outlineColorStr >> x1 >> y1 >> x2 >> y2 >> x3 >> y3))
	{
		throw std::invalid_argument("Invalid input format. Expected: RRGGBB RRGGBB x1 y1 x2 y2 x3 y3");
	}

	if (!IsValidColorFormat(fillColorStr) || !IsValidColorFormat(outlineColorStr))
	{
		throw std::invalid_argument("Invalid color format");
	}

	uint32_t fillColor = ColorToInt(fillColorStr);
	uint32_t outlineColor = ColorToInt(outlineColorStr);

	auto triangle = std::make_unique<CTriangle>(CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3), fillColor, outlineColor);
	m_shapes.push_back(std::move(triangle));
}

void CShapesController::AddLine()
{
	m_output << "\n<color> <start pos> <end pos> \n";

	std::string colorStr;
	double x1, y1, x2, y2;

	if (!(m_input >> colorStr >> x1 >> y1 >> x2 >> y2))
	{
		throw std::invalid_argument("Invalid input format. Expected: RRGGBB x1 y1 x2 y2");
	}

	if (!IsValidColorFormat(colorStr))
	{
		throw std::invalid_argument("Invalid color format. Expected RRGGBB (6 hex digits)");
	}

	uint32_t outlineColor = ColorToInt(colorStr);
	auto line = std::make_unique<CLineSegment>(CPoint(x1, y1), CPoint(x2, y2), outlineColor);
	m_shapes.push_back(std::move(line));
}

void CShapesController::DrawAllShapes(sf::RenderWindow& window)
{
	CCanvas canvas(window);
	for (auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

uint32_t CShapesController::ColorToInt(const std::string& line)
{
	uint32_t num;
	std::stringstream ss;
	ss << std::hex << line << "FF";
	ss >> num;
	return num;
}
