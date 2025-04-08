#pragma once
#include "CPoint.h"
#include "ISolidShape.h"
#include "ICanvasDrawable.h"

class CTriangle : public ISolidShape, public ICanvasDrawable
{
public:
	CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t fillColor, uint32_t outlineColor);

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] uint32_t GetFillColor() const override;

	[[nodiscard]] CPoint GetVertex1() const;
	[[nodiscard]] CPoint GetVertex2() const;
	[[nodiscard]] CPoint GetVertex3() const;

	void Draw(ICanvas& canvas) override;
private:
	CPoint m_vertex1, m_vertex2, m_vertex3;
	uint32_t m_fillColor;
	uint32_t m_outlineColor;
};
