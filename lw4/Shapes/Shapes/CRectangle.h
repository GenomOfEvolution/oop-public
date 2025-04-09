#pragma once
#include "CPoint.h"
#include "ISolidShape.h"
#include "ICanvasDrawable.h"
#include <string>

class CRectangle : public ISolidShape
{
public:
	CRectangle(CPoint startPos, double width, double height, uint32_t fillColor, uint32_t outlineColor);

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] uint32_t GetFillColor() const override;

	[[nodiscard]] CPoint GetLeftTop() const;
	[[nodiscard]] CPoint GetRightBottom() const;
	[[nodiscard]] double GetWidth() const;
	[[nodiscard]] double GetHeight() const;

	void Draw(ICanvas& canvas) override;
private:
	CPoint m_startPos;
	double m_width;
	double m_height;

	uint32_t m_fillColor;
	uint32_t m_outlineColor;
};
