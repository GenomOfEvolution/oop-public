#pragma once
#include "ISolidShape.h"
#include "ICanvasDrawable.h"
#include "CPoint.h"

class CCircle : public ISolidShape, public ICanvasDrawable
{
public:
	CCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor);

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] uint32_t GetFillColor() const override;

	[[nodiscard]] CPoint GetCenter() const;

	void Draw(ICanvas& canvas) override;

private:
	CPoint m_center;
	double m_radius;
	uint32_t m_fillColor;
	uint32_t m_outlineColor;
};
