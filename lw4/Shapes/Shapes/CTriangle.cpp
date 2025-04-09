#include "CTriangle.h"

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t fillColor, uint32_t outlineColor)
	: m_vertex1(vertex1), m_vertex2(vertex2), m_vertex3(vertex3), m_fillColor(fillColor), m_outlineColor(outlineColor)
{
	// ѕроверить возможность подсчета площади
	double determinant = (m_vertex1.GetX() - m_vertex3.GetX()) * (m_vertex2.GetY() - m_vertex3.GetY())
		- (m_vertex2.GetX() - m_vertex3.GetX()) * (m_vertex1.GetY() - m_vertex3.GetY());

	if (determinant == 0)
	{
		throw std::invalid_argument("Invalid triangle coords");
	}
}

double CTriangle::GetArea() const
{
	double determinant = (m_vertex1.GetX() - m_vertex3.GetX()) * (m_vertex2.GetY() - m_vertex3.GetY())
		- (m_vertex2.GetX() - m_vertex3.GetX()) * (m_vertex1.GetY() - m_vertex3.GetY());

	return 0.5 * abs(determinant);
}

double CTriangle::GetPerimeter() const
{
	const double line1 = m_vertex1.GetDistanceTo(m_vertex2);
	const double line2 = m_vertex2.GetDistanceTo(m_vertex3);
	const double line3 = m_vertex3.GetDistanceTo(m_vertex1);

	return line1 + line2 + line3;
}

std::string CTriangle::ToString() const
{
	return "Vertex 1: " + m_vertex1.ToString() + "\n"
		 + "Vertex 2: " + m_vertex2.ToString() + "\n"
		 + "Vertex 3: " + m_vertex3.ToString() + "\n"
		 + "Fill color: #" + GetColorHex(m_fillColor) + "\n"
		 + "Outline color: #" + GetColorHex(m_outlineColor) + "\n";
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

void CTriangle::Draw(ICanvas& canvas)
{
	canvas.FillPolygon(
		{ m_vertex1, m_vertex2, m_vertex3 },
		m_fillColor,
		m_outlineColor
	);
}
