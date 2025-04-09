#pragma once
#include "ICanvas.h"
#include <SFML/Graphics.hpp> 

class CCanvas : public ICanvas
{
public:
	explicit CCanvas(sf::RenderWindow& window);

	void DrawLine(CPoint startPoint, CPoint endPoint, uint32_t lineColor) const override;
	void FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor, uint32_t outlineColor) const override;
	void FillRect(CPoint coordinates, double width, double height, uint32_t fillColor, uint32_t outlineColor) const override;
	void FillCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor) const override;

private:
	sf::RenderWindow& m_window;
};
