﻿#pragma once
#include <string>
#include <SFML/Graphics.hpp>

// можно убрать C, а I для интрефейса оставить

class CPoint
{
public:
	CPoint(double x = 0, double y = 0) : m_x(x), m_y(y) {	}
	
	[[nodiscard]] double GetX() const { return m_x; }
	[[nodiscard]] double GetY() const { return m_y; }
	[[nodiscard]] double GetDistanceTo(const CPoint& other) const;

	[[nodiscard]] std::string ToString() const;
	// абстрагироваться от sfml
	[[nodiscard]] sf::Vector2f ToSFML() const;
	
private:
	double m_x;
	double m_y;
};
