#include "CPoint.h"
#include <cmath>

double CPoint::GetDistanceTo(const CPoint& other) const
{
	return std::hypot(m_x - other.m_x, m_y - other.m_y);
}

std::string CPoint::ToString() const
{
	return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
}

sf::Vector2f CPoint::ToSFML() const
{
	return sf::Vector2f(static_cast<float>(m_x), static_cast<float>(m_y));
}
