#define _USE_MATH_DEFINES
#include <math.h>
#include "CCircle.h"


CCircle::CCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor) 
    : m_center(center), m_radius(radius), m_fillColor(fillColor), m_outlineColor(outlineColor)
{
}

double CCircle::GetArea() const
{
    return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
    return 2 * M_PI * m_radius;
}

std::string CCircle::ToString() const
{
    return "Circle at " + m_center.ToString() + "\n"
        + "Radius: " + std::to_string(m_radius) + "\n"
        + "Fill color: #" + GetColorHex(m_fillColor) + "\n"
        + "Outline color: #" + GetColorHex(m_outlineColor) + "\n";
}

uint32_t CCircle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CCircle::GetCenter() const
{
    return m_center;
}

void CCircle::Draw(ICanvas& canvas)
{
}
