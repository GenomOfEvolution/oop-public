#pragma once
#include "IShape.h"
#include "CPoint.h"
#include "ICanvasDrawable.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t lineColor);

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] CPoint GetStartPoint() const;
	[[nodiscard]] CPoint GetEndPoint() const;
	[[nodiscard]] std::string ToString() const override;

	void Draw(ICanvas& canvas) override;

private:
	CPoint m_startPoint, m_endPoint;
	uint32_t m_color;
};