#include "CCanvasMock.h"

CCanvasMock::CCanvasMock(std::ostream& output)
	: m_output(output)
{
}

void CCanvasMock::DrawLine(CPoint startPoint, CPoint endPoint, uint32_t lineColor) const
{
	m_output << "Drawing line:\n";
	m_output << "Start at " + startPoint.ToString() << "\n";
	m_output << "End at " + endPoint.ToString() << "\n";
	m_output << "Color " << lineColor << "\n";
}

void CCanvasMock::FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor, uint32_t outlineColor) const
{
	m_output << "Drawing polygon:\n";
	m_output << "With points\n";
	
	for (CPoint p : points)
	{
		m_output << p.ToString() << "\n";
	}

	m_output << "Fill color " << fillColor << "\n";
	m_output << "Outline color " << outlineColor << "\n";
}

void CCanvasMock::FillRect(CPoint coordinates, double width, double height, uint32_t fillColor, uint32_t outlineColor) const
{
	m_output << "Drawing rect:\n";
	m_output << "Width " << width << "\n";
	m_output << "Height " << height << "\n";
	m_output << "Fill color " << fillColor << "\n";
	m_output << "Outline color " << outlineColor << "\n";
}

void CCanvasMock::FillCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor) const
{
	m_output << "Drawing circle:\n";
	m_output << "Center at " + center.ToString();
	m_output << "Radius " << radius << "\n";
	m_output << "Fill color " << fillColor << "\n";
	m_output << "Outline color " << outlineColor << "\n";
}
