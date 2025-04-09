#include "CCanvas.h"

CCanvas::CCanvas(sf::RenderWindow& window) : m_window(window)
{
}

void CCanvas::DrawLine(CPoint startPoint, CPoint endPoint, uint32_t lineColor) const
{
    sf::Vertex line[] = 
    {
        sf::Vertex(startPoint.ToSFML(), sf::Color(lineColor)),
        sf::Vertex(endPoint.ToSFML(), sf::Color(lineColor))
    };

    m_window.draw(line, 2, sf::Lines);
}

void CCanvas::FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor, uint32_t outlineColor) const
{
    sf::ConvexShape polygon;
    polygon.setPointCount(points.size());

    for (size_t i = 0; i < points.size(); ++i) 
    {
        polygon.setPoint(i, points[i].ToSFML());
    }

    polygon.setFillColor(sf::Color(fillColor));
    polygon.setOutlineColor(sf::Color(outlineColor));
    polygon.setOutlineThickness(1.0f);

    m_window.draw(polygon);
}

void CCanvas::FillRect(CPoint coordinates, double width, double height, uint32_t fillColor, uint32_t outlineColor) const
{
    sf::RectangleShape rect(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
    rect.setPosition(coordinates.ToSFML());
    rect.setFillColor(sf::Color(fillColor));
    rect.setOutlineColor(sf::Color(outlineColor));
    rect.setOutlineThickness(1.0f);

    m_window.draw(rect);
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor) const
{
    sf::CircleShape circle(static_cast<float>(radius));
    circle.setPosition(center.ToSFML() - sf::Vector2f((float)radius, (float)radius));
    circle.setFillColor(sf::Color(fillColor));
    circle.setOutlineColor(sf::Color(outlineColor));
    circle.setOutlineThickness(1.0f);

    m_window.draw(circle);
}
